from PyQt5 import QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import sys
from my_ui import Ui_MainWindow
import time
from time import sleep
from rclpy.node import Node
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry

class MinimalPublisher(Node):

    def __init__(self, send_back_function):
        super().__init__('minimal_publisher')
        self.vel_pub   = self.create_publisher(Twist, 'cmd_vel', 10)
        timer_period = 0.5  # seconds
        self.subscription = self.create_subscription(
            Odometry,
            'odom',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        self.send_back_function = send_back_function
        
        self.i = 0
    def pub_message(self,speed):
        msg = Twist()
        
        msg.linear.x  = speed;
        msg.angular.z = 0.0;
  
        self.vel_pub.publish(msg);
        print("pub speed is "+str(speed))
        
    def listener_callback(self, msg):
        
        self.send_back_function(msg.pose.pose.position.x,msg.pose.pose.position.y)
        
class RunningThread(QThread):
    def __init__(self, parent, signal):
        super(RunningThread, self).__init__(parent=parent)
        self.signal = signal
    def run(self):
        #sleep(3)
        
        self.minimal_publisher = MinimalPublisher(self.send_back_to_main_ui)

        rclpy.spin(self.minimal_publisher)
        rclpy.shutdown()
    def pub_message_by_thread(self,speed):
        self.minimal_publisher.pub_message(speed)
        
    def send_back_to_main_ui(self,positionX,positionY):
        
        self.signal.emit(positionX,positionY)
        
class MainWindow(QMainWindow):
    signal = pyqtSignal(float,float)
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui_connection()
        self.signal.connect(self.show_message)
        self.runningThread = RunningThread(self,self.signal)
        self.runningThread.start()
        self.speed = 0
        
    def ui_connection(self):
        
        self.ui.pushButton.clicked.connect(self.click_speed_up_button)
        self.ui.pushButton_2.clicked.connect(self.click_speed_down_button)
        self.ui.pushButton_3.clicked.connect(self.click_set_speed_button)
        self.ui.pushButton_4.clicked.connect(self.click_speed_0_button)
    
    @pyqtSlot(float,float)
    def show_message(self,positionX,positionY):
        self.ui.label_2.setText(str(positionX))
        self.ui.label_3.setText(str(positionY))
        
    def click_speed_up_button(self):
        self.speed +=0.1;
        self.runningThread.pub_message_by_thread(self.speed)
        
    def click_speed_down_button(self):
        self.speed -=0.1;
        self.runningThread.pub_message_by_thread(self.speed)
    def click_set_speed_button(self):
        setSpeed = self.ui.lineEdit.text()
        self.speed = float(setSpeed)
        self.runningThread.pub_message_by_thread(self.speed)
    def click_speed_0_button(self):
        self.speed =0.0;
        self.runningThread.pub_message_by_thread(self.speed)
    
if __name__ == "__main__":
    rclpy.init()
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())
    

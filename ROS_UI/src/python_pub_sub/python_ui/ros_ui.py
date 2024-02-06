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

class MinimalPublisher(Node):

    def __init__(self, send_back_function):
        super().__init__('minimal_publisher')
        self.publisher_ = self.create_publisher(String, 'topic', 10)
        timer_period = 0.5  # seconds
        self.subscription = self.create_subscription(
            String,
            'topic',
            self.listener_callback,
            10)
        self.subscription  # prevent unused variable warning
        self.send_back_function = send_back_function
        
        self.i = 0
    def pub_message(self):
        msg = String()
        msg.data = 'Hello World: %d' % self.i
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1
        
    def listener_callback(self, msg):
        
        self.send_back_function(msg.data)
        
class RunningThread(QThread):
    def __init__(self, parent, signal):
        super(RunningThread, self).__init__(parent=parent)
        self.signal = signal
    def run(self):
        #sleep(3)
        
        self.minimal_publisher = MinimalPublisher(self.send_back_to_main_ui)

        rclpy.spin(self.minimal_publisher)
        rclpy.shutdown()
    def pub_message_by_thread(self):
        self.minimal_publisher.pub_message()
        
    def send_back_to_main_ui(self,msd_data):
        
        self.signal.emit(msd_data)
        
class MainWindow(QMainWindow):
    signal = pyqtSignal(str)
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui_connection()
        self.signal.connect(self.show_message)
        self.runningThread = RunningThread(self,self.signal)
        self.runningThread.start()
        
    def ui_connection(self):
        self.setIDButton = self.ui.pushButton
        self.setIDButton.clicked.connect(self.buttonClick)
    
    @pyqtSlot(str)
    def show_message(self,msg):
        self.ui.label.setText(msg)
        
    def buttonClick(self):
        self.runningThread.pub_message_by_thread()
    
if __name__ == "__main__":
    rclpy.init()
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())
    

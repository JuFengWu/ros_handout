from PyQt5 import QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import sys
from my_ui import Ui_MainWindow
import time
from time import sleep
class RunningThread(QThread):
    def __init__(self, parent, signal):
        super(RunningThread, self).__init__(parent=parent)
        self.signal = signal
    def run(self):
        sleep(3)
        self.signal.emit("end running")
        
class MainWindow(QMainWindow):
    signal = pyqtSignal(str)
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui_connection()
        self.signal.connect(self.show_message)
        self.runningThread = RunningThread(self,self.signal)
        #self.runningThread.start()
        
    def ui_connection(self):
        self.setIDButton = self.ui.pushButton
        self.setIDButton.clicked.connect(self.buttonClick)
    
    @pyqtSlot(str)
    def show_message(self,msg):
        self.ui.label_2.setText(msg)
        
    def buttonClick(self):
        self.runningThread.start()
        self.ui.label_2.setText("start running")
    
if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())
    
    #app = QtWidgets.QApplication(sys.argv)
    #MainWindow = QtWidgets.QMainWindow()
    #ui = Ui_MainWindow()
    #ui.setupUi(MainWindow)
    #MainWindow.show()
    #sys.exit(app.exec_())

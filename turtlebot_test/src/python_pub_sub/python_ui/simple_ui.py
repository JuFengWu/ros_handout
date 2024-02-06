from PyQt5 import QtWidgets
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
import sys
from my_ui import Ui_MainWindow
import time
class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.ui_connection()
        
    def ui_connection(self):
        self.setIDButton = self.ui.pushButton
        self.setIDButton.clicked.connect(self.buttonClick)
        
    def buttonClick(self):
                
        self.ui.label_2.setText("hello")
    
if __name__ == "__main__":
    app = QApplication(sys.argv)

    window = MainWindow()
    window.show()

    sys.exit(app.exec_())
    

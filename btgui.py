import sys
import random
from PySide2.QtWidgets import (QApplication, QLabel, QPushButton,
                               QVBoxLayout, QWidget, QHBoxLayout)
from PySide2.QtCore import Slot, Qt

import serial

class MyWidget(QWidget):
    def __init__(self):
        QWidget.__init__(self)

        self.sndButton = QPushButton("Search and Destroy")
        self.tornadoButton = QPushButton("Tornado")
        self.ser = serial.Serial('COM8', write_timeout=0)

        self.layout = QVBoxLayout()
        self.layout.addWidget(self.sndButton)
        self.layout.addWidget(self.tornadoButton)
        self.setLayout(self.layout)
        
        #self.setStyleSheet("background-color:green;"
        #                   "border: 20px solid black;")
        #self.button.setStyleSheet("background-color:red;"
        #                          "color:orange;")
        #self.buttonOff.setStyleSheet("background-color:red;"
        #                             "color:orange;")

        # Connecting the signal
        self.sndButton.clicked.connect(self.snd)
        self.tornadoButton.clicked.connect(self.tornado)

    @Slot()
    def snd(self):
        self.ser.write(b'S\n\r')
        
    @Slot()
    def tornado(self):
        self.ser.write(b'T\n\r')

if __name__ == "__main__":
    app = QApplication(sys.argv)

    widget = MyWidget()
    widget.resize(800, 600)
    widget.show()

    sys.exit(app.exec_())
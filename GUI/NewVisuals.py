import PyQt5
import pyqtgraph as pg
from PyQt5.QtCore import pyqtSignal, QThread
import serial
from PyQt5.QtWidgets import QMainWindow, QApplication, QVBoxLayout, QHBoxLayout
import sys
import time

try:
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
except serial.SerialException:
    ser = None


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Balancer-GUI")
        self.setMinimumSize(800, 600)

        #---Daten die geplottet werden
        self.time_data = []  #x axis
        self.angle_data = [] #y axis

        self.current_time = time.time()
        self.startTime = time.time()


            #--- Daten aus Worker thread
        self.worker = Worker(ser)
        self.worker.start()

        self.worker.angle.connect(self.update_plot)



        #---Plot---
        #TODO Plot erstellen
        self.angle_plot = pg.PlotWidget()
        self.angle_plot.setTitle("Angle/t")
        self.angle_plot.setLabel("bottom", "t")
        self.angle_plot.setLabel("left", "angle")
        self.angle_plot.setYRange(-90, 90)
        self.curve = self.angle_plot.plot([], pen = "#006400")
        self.angle_plot.addLine(y=0, pen = pg.mkPen(color = "r", width = 1))

       #---Plot Style---
        self.angle_plot.setBackground("w")
        self.angle_plot.getAxis("left").setPen("k")
        self.angle_plot.getAxis("bottom").setPen("k")
        self.angle_plot.getAxis("left").setTextPen("k")
        self.angle_plot.getAxis("bottom").setTextPen("k")






        #---Layout---
        #Todo Layout erstellen
        vertikal_layout = QVBoxLayout()
        horizontal_layout = QHBoxLayout()

        vertikal_layout.addWidget(self.angle_plot)
        vertikal_layout.addLayout(horizontal_layout)

        self.setCentralWidget(self.angle_plot)



    def update_plot(self, angle):

        self.current_time = time.time() - self.startTime

        self.angle_data.append(angle)
        self.time_data.append(self.current_time)

        while len(self.time_data) > 0 and self.time_data[0]  < self.current_time-10:
            self.time_data.pop(0)
            self.angle_data.pop(0)

        self.curve.setData(self.time_data, self.angle_data)
        self.angle_plot.setXRange(self.current_time-10, self.current_time)




class Worker(QThread):
    angle = pyqtSignal(float)
    def __init__(self, ser):
        super().__init__()


        self.ser = ser

    def run(self):
        #---Daten Empfangen---
        while True:
            line = self.ser.readline().decode().strip()
            angle = float(line)
            self.angle.emit(angle) #Sendet daten an MainWindwo





            #---Daten Senden---



app = QApplication(sys.argv)
window = MainWindow()
window.show()
sys.exit(app.exec_())
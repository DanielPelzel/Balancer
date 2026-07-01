import queue

import PyQt5
import pyqtgraph as pg
from PyQt5.QtCore import pyqtSignal, QThread, QSettings
import serial
from PyQt5.QtWidgets import QMainWindow, QApplication, QVBoxLayout, QHBoxLayout, QSpinBox, QWidget, QLabel, \
    QDoubleSpinBox

import sys
import time

try:
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
except serial.SerialException:
    ser = None


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.settings= QSettings("Balancer", "PID")

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



        #---PAngle-lot---
        #TODO Plot erstellen
        self.angle_plot = pg.PlotWidget()
        self.angle_plot.setTitle("Angle/t")
        self.angle_plot.setLabel("bottom", "t")
        self.angle_plot.setLabel("left", "angle")
        self.angle_plot.setYRange(-90, 90)
        self.curve = self.angle_plot.plot([], pen = "#006400")
        self.angle_plot.addLine(y=0, pen = pg.mkPen(color = "r", width = 1))
        self.angle_plot.getPlotItem().getViewBox().setDefaultPadding(0)

       #---Angle-Plot Style---
        self.angle_plot.setBackground("w")
        self.angle_plot.getAxis("left").setPen("k")
        self.angle_plot.getAxis("bottom").setPen("k")
        self.angle_plot.getAxis("left").setTextPen("k")
        self.angle_plot.getAxis("bottom").setTextPen("k")

        #--P Spinbox Widget---
        self.p_widget = QDoubleSpinBox()
        self.p_widget.setRange(0,50)
        self.p_widget.setValue(5)
        self.p_widget.valueChanged.connect(self.send_pid)

        #---I SPinbox Widget---
        self.i_widget = QDoubleSpinBox()
        self.i_widget.setRange(0, 50)
        self.i_widget.setValue(0)
        self.i_widget.valueChanged.connect(self.send_pid)

        #---d Spinbox Widget---
        self.d_widget = QDoubleSpinBox()
        self.d_widget.setRange(0, 50)
        self.d_widget.setValue(0)
        self.d_widget.valueChanged.connect(self.send_pid)




        #---Layout---
        #Todo Layout erstellen
        vertikal_layout = QVBoxLayout()
        horizontal_layout1 = QHBoxLayout()
        horizontal_layout2 = QHBoxLayout()

        vertikal_layout.addWidget(self.angle_plot)
        vertikal_layout.addLayout(horizontal_layout1)
        vertikal_layout.addLayout(horizontal_layout2)

        horizontal_layout1.addWidget(QLabel("p"))
        horizontal_layout2.addWidget(self.p_widget)

        horizontal_layout1.addWidget(QLabel("i"))
        horizontal_layout2.addWidget(self.i_widget)

        horizontal_layout1.addWidget(QLabel("d"))
        horizontal_layout2.addWidget(self.d_widget)

        self.loadSettings()



        container = QWidget()
        container.setLayout(vertikal_layout)
        self.setCentralWidget(container)


    def update_plot(self, angle):
        """
        updated die Kurve vom Plot immer wenn ein neuer Wert per ser empfangen wid
        :param angle:
        :return:
        """

        self.current_time = time.time() - self.startTime

        #updated die Daten die geplottet werden
        self.angle_data.append(angle)
        self.time_data.append(self.current_time)

        #entfernt alte daten aus dem plot
        while len(self.time_data) > 0 and self.time_data[0]  < self.current_time-10:
            self.time_data.pop(0)
            self.angle_data.pop(0)

        self.curve.setData(self.time_data, self.angle_data)
        self.angle_plot.setXRange(self.current_time-10, self.current_time)

    def send_pid(self, angle):
        """Holt dich die PID DAaten sobald ein Wert geöndert wir dund sendet die per queue an den Worker thread """

        self.p = self.p_widget.value()
        self.i = self.i_widget.value()
        self.d = self.d_widget.value()

        self.worker.queue.put(f"p:{self.p}, i:{self.i}, d:{self.d}\n")

    def saveSettings(self):

        self.settings.setValue("p", self.p_widget.value())
        self.settings.setValue("i", self.i_widget.value())
        self.settings.setValue("d", self.d_widget.value())

    def loadSettings(self):

        self.p_widget.setValue(self.settings.value("p", defaultValue=5, type=float))
        self.i_widget.setValue(self.settings.value("i", defaultValue=0, type=float))
        self.d_widget.setValue(self.settings.value("d", defaultValue=0, type=float))

    def closeEvent(self, e):
        self.saveSettings()
        super().closeEvent(e)








class Worker(QThread):
    angle = pyqtSignal(float)
    def __init__(self, ser):
        super().__init__()


        self.ser = ser
        self.queue = queue.Queue()


    def run(self):
        #---Daten Empfangen---
        while True:
            line = self.ser.readline().decode().strip()
            angle = float(line)
            self.angle.emit(angle) #Sendet daten an MainWindwo

            #---Daten Senden---
            if not self.queue.empty():
                msg = self.queue.get()
                self.ser.write(msg.encode())




app = QApplication(sys.argv)
window = MainWindow()
window.show()
sys.exit(app.exec_())
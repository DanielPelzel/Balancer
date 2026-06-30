"""
Echtzeit-Winkelanzeige für den Balancer.
Liest den Neigungswinkel vom ESP32 (seriell) und zeigt ihn als scrollenden Graph an.
"""

import PyQt5
from PyQt5.QtCore import QRunnable, QObject, pyqtSignal, QThread
import serial.tools.list_ports
from PyQt5.QtWidgets import QMainWindow, QApplication
import sys
import pyqtgraph as pg
import time

#port finden

def findPort():
    ports = serial.tools.list_ports.comports()
    for port in ports:
        if "USB" in port.description or "UART" in port.description or "C210" in port.description:
            return port.device

    return None

port = findPort()


class Worker(QThread):
    """Hintergrund-Thread: liest Winkelwerte (Float, eine Zeile pro Wert) vom seriellen Port und sendet sie per Signal."""

    data = pyqtSignal(float)  # Signal: neuer Winkelwert → wird an update_plot weitergeleitet

    def __init__(self):
        super().__init__()
        self.ser = serial.Serial(port, baudrate=115200)
        self.running = True

    def run(self):
        """Liest in einer Schleife Zeilen vom ESP32, parst den Float und sendet ihn als Signal."""
        while self.running:
            try:
                line = self.ser.readline().decode().strip()
                angle = float(line)
                self.data.emit(angle)
            except:
                pass

    def stop(self):
        """Beendet den Thread sauber und schließt den seriellen Port."""
        self.running = False
        self.ser.close()
        self.wait()




class MainWindow(QMainWindow):
    """Hauptfenster: zeigt Winkel als gelbe Kurve (±90°), rote Linie bei 0° = Gleichgewicht, X-Achse scrollt (letzte 10 s)."""

    def __init__(self):
        super().__init__()

        self.start_time = time.time()
        self.current_time = time.time()

        self.angle_data = []
        self.time_data = []

        #Worker erstellen udn Signal verbinden
        self.worker = Worker()
        self.worker.data.connect(self.update_plot)
        self.worker.start()

        #plot Widget
        self.plot = pg.PlotWidget()
        self.plot.setWindowTitle("Balancer")
        self.plot.setTitle("Angle")
        self.plot.setLabel("left", "Grad")
        self.plot.setLabel("bottom", "Zeit (s)")
        self.plot.setYRange(-90, 90)
        self.plot.addLine(y=0, pen=pg.mkPen("r", width=1))

        self.curve = self.plot.plot([], pen="y")

        self.setCentralWidget(self.plot)

    def update_plot(self, angle):
        """Neuen Winkel anhängen, Punkte älter als 10 s löschen (Sliding Window), Kurve neu zeichnen."""
        self.angle_data.append(angle)
        self.current_time = time.time() - self.start_time 
        self.time_data.append(self.current_time)

        while len(self.time_data) > 0 and self.time_data[0] < self.current_time - 10:
            self.angle_data.pop(0)
            self.time_data.pop(0)

        self.curve.setData(self.time_data, self.angle_data)
        self.plot.setXRange(self.current_time - 10, self.current_time)



    def closeEvent(self, event):
        """Fenster schließen → Worker-Thread sauber stoppen."""
        self.worker.stop()
        event.accept()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())

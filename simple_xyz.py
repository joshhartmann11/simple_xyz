import serial
from serial.tools import list_ports
import struct


class XYZ:

    BAUD_RATE = 250000

    def __init__(self, port=None):
        self.setup(port) if port else self.auto_setup()

    def setup(self, port):
        if self.serial_connection:
            self.serial_connection.close()
        self.serial_connection = serial.Serial(port, baudrate=self.BAUD_RATE)

    def auto_setup(self):
        devices = [str(d) for d in list_ports.comports(True)]
        device_path = devices[0].split(" - ")[0]
        self.setup(device_path)

    def step(self, x:int, y:int, z:int, delay:int=2**14):
        bytes = struct.pack("iiih", x, y, z, delay)
        self.serial_connection.write(bytes)

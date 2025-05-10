import pytest
import serial
import time

SERIAL_PORT = "/dev/ttyUSB0"  # Aggiorna con la porta corretta su Windows, es: 'COM3'
BAUDRATE = 115200
TIMEOUT = 10

@pytest.fixture(scope="module")
def esp32_serial():
    ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=TIMEOUT)
    time.sleep(2)  # Attendi che la board si resetti
    yield ser
    ser.close()

def test_wifi_scan(esp32_serial):
    esp32_serial.write(b"TEST_WIFI_SCAN\n")
    output = esp32_serial.readline().decode(errors="ignore")
    assert "WIFI_SCAN_OK" in output, f"Unexpected output: {output}"

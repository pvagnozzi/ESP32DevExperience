import pytest
import serial
import time

SERIAL_PORT = "/dev/ttyUSB0"  # Update as needed for your system (e.g., 'COM3' on Windows)
BAUDRATE = 115200
TIMEOUT = 10

def send_command_and_expect(cmd, expected, timeout=5):
    with serial.Serial(SERIAL_PORT, BAUDRATE, timeout=timeout) as ser:
        time.sleep(2)  # Wait for ESP32 to reset
        ser.write((cmd + "\n").encode())
        output = ser.readline().decode(errors="ignore")
        assert expected in output, f"Expected '{expected}' in output, got: {output}"

# Example unit test for WiFi scan
@pytest.mark.esp32
def test_wifi_scan():
    send_command_and_expect("TEST_WIFI_SCAN", "WIFI_SCAN_OK")

# Example unit test for encryption/decryption
@pytest.mark.esp32
def test_encrypt_decrypt():
    send_command_and_expect("TEST_ENCRYPT_DECRYPT", "ENCRYPT_DECRYPT_OK")

# Example unit test for WiFi config save/load
@pytest.mark.esp32
def test_save_load_wifi_config():
    send_command_and_expect("TEST_SAVE_LOAD_WIFI_CONFIG", "SAVE_LOAD_WIFI_OK")

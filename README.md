# ESP32DevExperience

**Author:** Your Name (<your.email@example.com>)

## Description

ESP32DevExperience is an advanced development platform for ESP32, designed to provide a modern, automated, and secure environment for IoT, networking, and automation projects. The project includes:
- Responsive web UI for WiFi configuration (with Bootstrap on SPIFFS)
- HTTPS support (auto-generated certificates)
- MQTT over TLS
- WiFi management with FreeRTOS
- Secure credential storage (AES + NVS)
- LUA script support
- Automated build, Python/pytest testing, advanced CMake, and Boost support
- Wide set of C++ libraries for ESP32

## Main Features
- **Asynchronous web server** (ESPAsyncWebServer) on HTTP/HTTPS
- **WiFi configuration** from browser, with network scan and secure storage
- **LED management**: different blinking based on WiFi status
- **MQTT support** (PubSubClient) also over TLS
- **SPIFFS/LittleFS file system** for web resources, certificates, LUA scripts
- **Support for BLE, FTP, UDP, mDNS, Ping, Time, Email, base64, Boost, Lua**
- **Automated testing**: pytest, pytest-embedded, rerunfailures, ignore-test-results
- **Certificate generation scripts** (Bash/PowerShell)
- **Automatic workload installation** (Windows/Linux/macOS)

## Workload Installation

### Windows
```powershell
cd scripts/workload
./install_workload.ps1
```

### Linux/macOS
```sh
cd scripts/workload
bash install_workfload.sh
```

## SSL/TLS Certificate Generation

### Bash (Linux/macOS/WSL)
```sh
cd scripts/cert
bash generate_cert.sh
```

### PowerShell (Windows)
```powershell
cd scripts/cert
./generate_cert.ps1
```

Certificates will be automatically copied to `data/certs` for SPIFFS deployment.

## Build and Deploy

1. **Generate certificates** (see above)
2. **Copy Bootstrap**: download `bootstrap.min.css` and `bootstrap.bundle.min.js` from [getbootstrap.com](https://getbootstrap.com/) and place them in `data/webui/bootstrap/`
3. **Build and upload**:
   - From VSCode: use PlatformIO tasks (Build/Upload)
   - From terminal:
     ```sh
     pio run --target upload --environment esp32dev
     pio run --target uploadfs --environment esp32dev
     ```

## Libraries and Software Used

- [PlatformIO](https://platformio.org/) ([docs](https://docs.platformio.org/en/latest/))
- [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer) ([docs](https://github.com/me-no-dev/ESPAsyncWebServer#documentation))
- [AsyncTCP](https://github.com/me-no-dev/AsyncTCP) ([docs](https://github.com/me-no-dev/AsyncTCP#documentation))
- [ArduinoJson](https://arduinojson.org/) ([docs](https://arduinojson.org/v6/doc/))
- [WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi) ([docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/libraries.html#wifi))
- [Preferences](https://github.com/espressif/arduino-esp32/tree/master/libraries/Preferences) ([docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/libraries.html#preferences))
- [LittleFS](https://github.com/lorol/LITTLEFS) ([docs](https://github.com/lorol/LITTLEFS#documentation))
- [PubSubClient](https://pubsubclient.knolleary.net/) ([docs](https://pubsubclient.knolleary.net/api))
- [BLE](https://github.com/nkolban/ESP32_BLE_Arduino) ([docs](https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/))
- [ESPmDNS](https://github.com/espressif/arduino-esp32/tree/master/libraries/ESPmDNS) ([docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/libraries.html#mdns))
- [ESP32Time](https://github.com/fbiego/ESP32Time) ([docs](https://github.com/fbiego/ESP32Time#usage))
- [ESP32Ping](https://github.com/marian-craciunescu/ESP32Ping) ([docs](https://github.com/marian-craciunescu/ESP32Ping#usage))
- [ESP32 Mail Client](https://github.com/mobizt/ESP-Mail-Client) ([docs](https://github.com/mobizt/ESP-Mail-Client#documentation))
- [boostorg/boost](https://www.boost.org/) ([docs](https://www.boost.org/doc/libs/1_83_0/))
- [base64](https://github.com/Densaugeo/base64_arduino) ([docs](https://github.com/Densaugeo/base64_arduino#usage))
- [ESP32FtpServer](https://github.com/ldab/ESP32FtpServer) ([docs](https://github.com/ldab/ESP32FtpServer#usage))
- [ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP) ([docs](https://github.com/me-no-dev/ESPAsyncUDP#documentation))
- [WiFiClientSecure](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFiClientSecure) ([docs](https://docs.espressif.com/projects/arduino-esp32/en/latest/libraries.html#wificlientsecure))
- [ESP_Mail_Client](https://github.com/mobizt/ESP-Mail-Client) ([docs](https://github.com/mobizt/ESP-Mail-Client#documentation))
- [Lua](https://www.lua.org/) ([docs](https://www.lua.org/manual/5.3/))
- [OpenSSL](https://www.openssl.org/) ([docs](https://www.openssl.org/docs/))
- [Bootstrap](https://getbootstrap.com/) ([docs](https://getbootstrap.com/docs/5.3/getting-started/introduction/))
- [pytest](https://docs.pytest.org/en/stable/) ([docs](https://docs.pytest.org/en/stable/))
- [pytest-embedded](https://github.com/espressif/pytest-embedded) ([docs](https://docs.espressif.com/projects/pytest-embedded/en/latest/))
- [pytest-rerunfailures](https://github.com/pytest-dev/pytest-rerunfailures) ([docs](https://pypi.org/project/pytest-rerunfailures/))
- [pytest-ignore-test-results](https://pypi.org/project/pytest-ignore-test-results/) ([docs](https://pypi.org/project/pytest-ignore-test-results/))

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

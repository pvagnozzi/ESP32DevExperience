/*
 * Example ESP32 FreeRTOS project: WiFi Manager Web Portal
 * - Serves a web page on port 80 to scan WiFi networks
 * - Allows user to select SSID and enter password
 * - Credentials are encrypted and saved to flash (NVS)
 * - LED blinks fast if WiFi not configured, slow if configured
 *
 * PlatformIO: Add dependencies in platformio.ini:
 *   [env:esp32dev]
 *   platform = espressif32
 *   board = esp32dev
 *   framework = arduino
 *   lib_deps =
 *     ESPAsyncWebServer
 *     AsyncTCP
 *     ArduinoJson
 *     WiFi
 *     Preferences
 *     base64
 */

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <Preferences.h>
#include <mbedtls/aes.h>
#include <FS.h>
#include <SPIFFS.h>
#include <LittleFS.h>
#include <ESPmDNS.h>
#include <ESP32Ping.h>
#include <ESP32Time.h>
#include <base64.h>
#include <PubSubClient.h>
#include <BLEDevice.h>
#include <ESP32FtpServer.h>
#include <ESPAsyncUDP.h>
#include <WiFiClientSecure.h>
#include <ESP_Mail_Client.h>

#define LED_PIN 2
#define BLINK_FAST 200
#define BLINK_SLOW 1000
#define ENCRYPTION_KEY "mySuperSecretKey!" // 16 bytes for AES-128

AsyncWebServer server(80);
AsyncWebServer secureServer(443);
Preferences preferences;

String ssid, password;
bool wifiConfigured = false;

void blinkTask(void *param) {
    while (1) {
        digitalWrite(LED_PIN, HIGH);
        vTaskDelay((wifiConfigured ? BLINK_SLOW : BLINK_FAST) / portTICK_PERIOD_MS);
        digitalWrite(LED_PIN, LOW);
        vTaskDelay((wifiConfigured ? BLINK_SLOW : BLINK_FAST) / portTICK_PERIOD_MS);
    }
}

String encrypt(const String &plain) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    uint8_t key[16];
    memcpy(key, ENCRYPTION_KEY, 16);
    mbedtls_aes_setkey_enc(&aes, key, 128);
    size_t len = plain.length();
    size_t paddedLen = ((len + 15) / 16) * 16;
    uint8_t input[32] = {0};
    uint8_t output[32] = {0};
    memcpy(input, plain.c_str(), len);
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, input, output);
    mbedtls_aes_free(&aes);
    String encoded = base64::encode(output, paddedLen);
    return encoded;
}

String decrypt(const String &cipher) {
    mbedtls_aes_context aes;
    mbedtls_aes_init(&aes);
    uint8_t key[16];
    memcpy(key, ENCRYPTION_KEY, 16);
    mbedtls_aes_setkey_dec(&aes, key, 128);
    std::vector<uint8_t> decoded = base64::decode(cipher);
    uint8_t output[32] = {0};
    mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, decoded.data(), output);
    mbedtls_aes_free(&aes);
    return String((char*)output);
}

void saveWiFiConfig(const String &ssid, const String &pass) {
    preferences.begin("wifi", false);
    preferences.putString("ssid", encrypt(ssid));
    preferences.putString("pass", encrypt(pass));
    preferences.end();
}

bool loadWiFiConfig(String &ssid, String &pass) {
    preferences.begin("wifi", true);
    String encSsid = preferences.getString("ssid", "");
    String encPass = preferences.getString("pass", "");
    preferences.end();
    if (encSsid.length() > 0 && encPass.length() > 0) {
        ssid = decrypt(encSsid);
        pass = decrypt(encPass);
        return true;
    }
    return false;
}

void handleRoot(AsyncWebServerRequest *request) {
    if (!SPIFFS.begin(true)) {
        request->send(500, "text/plain", "SPIFFS Mount Failed");
        return;
    }
    File file = SPIFFS.open("/index.html", "r");
    if (!file) {
        request->send(500, "text/plain", "Failed to open HTML file");
        return;
    }
    String html = file.readString();
    file.close();
    // Optionally, you can inject scanned SSIDs dynamically here
    int n = WiFi.scanNetworks();
    String options = "";
    for (int i = 0; i < n; ++i) {
        options += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
    }
    html.replace("{{SSID_OPTIONS}}", options);
    request->send(200, "text/html", html);
}

void handleSave(AsyncWebServerRequest *request) {
    if (request->hasParam("ssid", true) && request->hasParam("pass", true)) {
        String newSsid = request->getParam("ssid", true)->value();
        String newPass = request->getParam("pass", true)->value();
        saveWiFiConfig(newSsid, newPass);
        request->send(200, "text/html", "<html><body>Saved! Rebooting...</body></html>");
        delay(1000);
        ESP.restart();
    } else {
        request->send(400, "text/html", "<html><body>Missing parameters</body></html>");
    }
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    xTaskCreatePinnedToCore(blinkTask, "Blink", 2048, NULL, 1, NULL, 1);
    WiFi.mode(WIFI_STA);
    SPIFFS.begin(true);
    wifiConfigured = loadWiFiConfig(ssid, password);
    if (wifiConfigured) {
        WiFi.begin(ssid.c_str(), password.c_str());
    }
    // HTTPS certificate/key loading
    File cert = SPIFFS.open("/certs/server.crt", "r");
    File key = SPIFFS.open("/certs/server.key", "r");
    String certStr = cert.readString();
    String keyStr = key.readString();
    cert.close();
    key.close();
    if (certStr.length() > 0 && keyStr.length() > 0) {
        secureServer.beginSecure(certStr.c_str(), keyStr.c_str(), "");
    }
    server.on("/", HTTP_GET, handleRoot);
    server.on("/save", HTTP_POST, handleSave);
    server.begin();
    secureServer.on("/", HTTP_GET, handleRoot);
    secureServer.on("/save", HTTP_POST, handleSave);
}

void loop() {
    // Nothing, FreeRTOS tasks handle everything
}

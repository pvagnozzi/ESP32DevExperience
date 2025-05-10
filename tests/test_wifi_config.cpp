#include <Arduino.h>
#include <unity.h>
#include <WiFi.h>
#include <Preferences.h>

extern void saveWiFiConfig(const String &ssid, const String &pass);
extern bool loadWiFiConfig(String &ssid, String &pass);

void test_save_and_load_wifi_config() {
    String ssid = "TestSSID";
    String pass = "TestPass";
    saveWiFiConfig(ssid, pass);
    String loadedSsid, loadedPass;
    bool ok = loadWiFiConfig(loadedSsid, loadedPass);
    TEST_ASSERT_TRUE(ok);
    TEST_ASSERT_EQUAL_STRING(ssid.c_str(), loadedSsid.c_str());
    TEST_ASSERT_EQUAL_STRING(pass.c_str(), loadedPass.c_str());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_save_and_load_wifi_config);
    UNITY_END();
}

void loop() {}

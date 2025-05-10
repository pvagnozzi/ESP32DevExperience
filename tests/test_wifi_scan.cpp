#include <Arduino.h>
#include <unity.h>
#include <WiFi.h>

void test_wifi_scan() {
    WiFi.mode(WIFI_STA);
    int n = WiFi.scanNetworks();
    TEST_ASSERT_GREATER_OR_EQUAL(0, n); // Should not crash, n >= 0
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_wifi_scan);
    UNITY_END();
}

void loop() {}

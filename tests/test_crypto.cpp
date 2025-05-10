#include <Arduino.h>
#include <unity.h>

void test_encrypt_decrypt() {
    String original = "TestPassword123";
    String encrypted = encrypt(original);
    String decrypted = decrypt(encrypted);
    TEST_ASSERT_EQUAL_STRING(original.c_str(), decrypted.c_str());
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_encrypt_decrypt);
    UNITY_END();
}

void loop() {}

#include "utils/Utils.h"
#include "CppUTest/TestHarness.h"
#undef _L

TEST_GROUP(TEST_UTILS){};

#define JWT_PAYLOAD_EMAIL    "email"
#define JWT_PAYLOAD_PASSWORD "password"
#define JWT_LOGIN_EXPIRATION  30

TEST(TEST_UTILS, TEST_JWT) {
    {
        unordered_map<string, string> payload({
            {JWT_PAYLOAD_EMAIL,    "email"},
            {JWT_PAYLOAD_PASSWORD, "password"}
        });

        auto token = Utils::JWTEncode(payload, JWT_LOGIN_EXPIRATION);
        CHECK(Utils::JWTCheck(token, {JWT_PAYLOAD_EMAIL, JWT_PAYLOAD_PASSWORD}))
    }
}

TEST(TEST_UTILS, TEST_JWT_CLAIMS) {
    {
        unordered_map<string, string> payload({
            {JWT_PAYLOAD_EMAIL,    "email"},
            {JWT_PAYLOAD_PASSWORD, "password"}
        });

        auto token = Utils::JWTEncode(payload, JWT_LOGIN_EXPIRATION);

        string email = Utils::JWTGetClaim(token, JWT_PAYLOAD_EMAIL);
        string password = Utils::JWTGetClaim(token, JWT_PAYLOAD_PASSWORD);

        STRCMP_EQUAL("email", email.c_str())
        STRCMP_EQUAL("password", password.c_str())
    }
}

TEST(TEST_UTILS, TEST_HASH) {
    {
        string password = "password";
        string hash1 = Utils::hash(password);
        string hash2 = Utils::hash(password);

        CHECK(hash1 == hash2)
    }
}
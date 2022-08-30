#include <random>
#include <openssl/sha.h>
#include "utils/Utils.h"
#include "utils/Log.h"
#include "jwt/jwt.hpp"

#define UTILS_UNIT "UTILS"

#define JWT_SECRET "secret"
#define JWT_ALGO   "HS256"
#define JWT_EXP    "exp"

using namespace jwt::params;

int Utils::getRandom(int a, int b) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(a, b);

    return dist(gen);
}

string Utils::JWTEncode(unordered_map<string, string>& payloadData, int expSeconds) {
    jwt::jwt_object obj{
        algorithm(JWT_ALGO),
        payload(payloadData),
        secret(JWT_SECRET)
    };

    obj.add_claim(JWT_EXP, chrono::system_clock::now() + chrono::seconds{expSeconds});

    return obj.signature();
}

bool Utils::JWTCheck(const string& token, const vector<string>& payload) {
    try {
        auto dec = jwt::decode(token, algorithms({JWT_ALGO}), secret(JWT_SECRET), verify(true));

        for (auto& key: payload) {
            if (!dec.payload().has_claim(key)) {
                return false;
            }
        }
    } catch (exception& ex) {
        Log::LOG_ERROR(UTILS_UNIT, ex.what());
        return false;
    }

    return true;
}

string Utils::JWTGetClaim(const string& token, const string& claim) {
    auto dec = jwt::decode(token, algorithms({JWT_ALGO}), secret(JWT_SECRET));

    return dec.payload().get_claim_value<string>(claim);
}

string Utils::hash(const string& input) {
    unsigned char md[SHA256_DIGEST_LENGTH] = {};
    SHA256_CTX context;
    stringstream shastr;

    SHA256_Init(&context);
    SHA256_Update(&context, input.c_str(), input.size());
    SHA256_Final(md, &context);

    shastr << hex << setfill('0');
    for (const auto &byte: md) {
        shastr << setw(2) << (int) byte;
    }

    return shastr.str();
}
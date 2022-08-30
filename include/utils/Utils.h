#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Utils {
public:
    static int getRandom(int a, int b);

    static string JWTEncode(unordered_map<string, string>& payloadData, int expSeconds);
    static bool JWTCheck(const string& token, const vector<string>& payload);
    static string JWTGetClaim(const string& token, const string& claim);

    static string hash(const string& input);
};
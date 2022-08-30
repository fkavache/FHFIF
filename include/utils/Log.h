#pragma once

#include <iostream>

using namespace std;

class Log {
public:
    static void LOG_INFO(const string& unit, const string& message);
    static void LOG_ERROR(const string& unit, const string& message);
};

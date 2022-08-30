#include "utils/Log.h"

void Log::LOG_INFO(const string& unit, const string& message) {
    cout << "[" << unit << "] " << message << endl;
}

void Log::LOG_ERROR(const string& unit, const string& message) {
    cerr << "[" << unit << "] " << message << endl;
}
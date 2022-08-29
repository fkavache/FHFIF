#include "CppUTest/CommandLineTestRunner.h"

int main(int argc, const char **argv) {
    MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
    return RUN_ALL_TESTS(argc, argv);
}

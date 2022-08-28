set(SQLAPI ${PROJECT_SOURCE_DIR}/lib/lib/libsqlapi.a)

set(MEMLEAK_DETECTOR "-include ${PROJECT_SOURCE_DIR}/lib/lib/include/CppUTest/MemoryLeakDetectorMallocMacros.h")
set(NEW_MEMLEAK_DETECTOR "-include ${PROJECT_SOURCE_DIR}/lib/lib/include/CppUTest/MemoryLeakDetectorNewMacros.h")
set(CPPUTEST ${PROJECT_SOURCE_DIR}/lib/lib/libCppUTest.a)

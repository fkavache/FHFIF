cmake_minimum_required(VERSION 3.22)
project(FHFIF)

set(CMAKE_CXX_STANDARD 17)

include(cmake/Dependencies.cmake)
include_directories("include")
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# TODO: [vacheka]
include_directories("C:/boost/include/boost-1_79")
link_directories("C:/boost/lib")

file(GLOB SOURCE_FILES
        src/*.cpp
        src/dal/*.cpp
        src/model/*.cpp
        src/utils/*.cpp
        src/controller/*.cpp
        src/api/*.cpp)
file(GLOB HEADER_FILES
        include/*.h
        include/dal/*.h
        include/model/*.h
        include/utils/*.h
        include/controller/*.h
        include/api/*.h)
file(GLOB TEST_FILES
        test/*.h
        test/*.cpp
        test/dal/*.cpp
        test/model/*.cpp
        test/utils/*.cpp
        test/controller/*.cpp
        test/api/*.cpp)

add_library(${PROJECT_NAME}_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib ${SQLAPI} ${OPENSSL_LIBRARIES} version ws2_32 wsock32)

add_executable(test_${PROJECT_NAME} ${TEST_FILES})
target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME}_lib ${CPPUTEST} ${SQLAPI} ${OPENSSL_LIBRARIES} version ws2_32 wsock32)


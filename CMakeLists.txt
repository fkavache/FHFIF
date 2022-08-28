cmake_minimum_required(VERSION 3.22)
project(FHFIF)

set(CMAKE_CXX_STANDARD 17)

include(cmake/Dependencies.cmake)
include_directories("${PROJECT_SOURCE_DIR}/lib/include")

file(GLOB SOURCE_FILES
        src/*.cpp)
file(GLOB HEADER_FILES
        include/*.h)
file(GLOB TEST_FILES
        "test/*.h"
        "test/*.cpp")

add_library(${PROJECT_NAME}_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib ${SQLAPI})

add_executable(test_${PROJECT_NAME} ${TEST_FILES})
target_link_libraries(test_${PROJECT_NAME} ${PROJECT_NAME}_lib ${CPPUTEST})


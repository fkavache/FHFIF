cmake_minimum_required(VERSION 3.22)
project(FHFIF)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES
        src/*.cpp)
file(GLOB HEADER_FILES
        include/*.h)

add_library(FHFIF_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} FHFIF_lib)

cmake_minimum_required(VERSION 3.22)
project(hue_example CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/EDK)

set(files src/main.cpp src/Terminal.h src/Terminal.cpp src/RainbowEffect.h src/RainbowEffect.cpp)
add_executable (hue_example ${files})
target_link_libraries(hue_example huestream)

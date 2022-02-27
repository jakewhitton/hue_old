cmake_minimum_required(VERSION 3.22)
project(hue_example CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/EDK)

set(files src/main.cpp src/Terminal.h src/Terminal.cpp src/MultiBridgeRenderer.h src/MultiBridgeRenderer.cpp src/BridgeRenderer.h src/BridgeRenderer.cpp src/Config.h src/Config.cpp src/RenderEffect.h src/RenderEffect.cpp)
add_executable (hue_example ${files})
target_link_libraries(hue_example huestream)

cmake_minimum_required(VERSION 3.22)
project(hue_example CXX)

add_subdirectory(${PROJECT_SOURCE_DIR}/libs/EDK)

# EDK dependency
#include(ExternalProject)
#ExternalProject_Add(EDK
#  PREFIX EDK
#  GIT_SUBMODULES git@github.com:PhilipsHue/EDK.git
#  SOURCE_DIR ${PROJECT_SOURCE_DIR}/libs/EDK
#  CMAKE_ARGS -DBUILD_TEST=OFF -DBUILD_EXAMPLES=OFF -DBUILD_SWIG=OFF -DBUILD_WITH_RTTI=OFF -DCMAKE_INSTALL_P#REFIX=${CMAKE_BINARY_DIR}/EDK/install
#)

#set(EDK_INCLUDE_DIR
#  ${PROJECT_SOURCE_DIR}/libs/EDK/libhuestream
#  ${PROJECT_SOURCE_DIR}/libs/EDK/libhuestream/support/include
#  ${PROJECT_SOURCE_DIR}/libs/EDK/libhuestream/bridgediscovery/include
#  ${CMAKE_BINARY_DIR}/EDK/src/EDK-build/external_install/include
#)
#set(EDK_LIB_DIR
#  ${CMAKE_BINARY_DIR}/EDK/src/EDK-build/libhuestream/huestream
#  ${CMAKE_BINARY_DIR}/EDK/src/EDK-build/libhuestream/bridgediscovery
#  ${CMAKE_BINARY_DIR}/EDK/src/EDK-build/libhuestream/support
#  ${CMAKE_BINARY_DIR}/EDK/src/EDK-build/external_install/lib
#)

#add_library (huestream STATIC IMPORTED)
#set_target_properties(huestream
#  PROPERTIES
#  IMPORTED_LOCATION
#  ${CMAKE_BINARY_DIR}/EDK/src/EDK-build/libhuestream/huestream/libhuestream.a
#)

#add_library (bridgediscovery STATIC IMPORTED)
#set_target_properties(bridgediscovery
#  PROPERTIES
#  IMPORTED_LOCATION
#  ${CMAKE_BINARY_DIR}/EDK/src/EDK-build/libhuestream/bridgediscovery/libbridge_#discovery.a
#)

#add_library (support STATIC IMPORTED)
#set_target_properties(support
#  PROPERTIES
#  IMPORTED_LOCATION
#  ${CMAKE_BINARY_DIR}/EDK/src/EDK-build/libhuestream/support/libsupport.a
#)

set(files src/main.cpp src/Terminal.h src/Terminal.cpp src/RainbowEffect.h src/RainbowEffect.cpp)
#include_directories(${EDK_INCLUDE_DIR})
#link_directories(${EDK_LIB_DIR})
add_executable (hue_example ${files})
target_link_libraries(hue_example huestream)
#target_link_libraries(hue_example
#  huestream.a
#  bridge_discovery.a
#  support.a
#  curl.a
#  edtls_client.a
#  json.a
#  mbedcl_wrapper.a
#  mbedcrypto.a
#  mbedtls.a
#  mbedx509.a
#  mdns_responder.a
#  nghttp2_static.a
#  pthread
#)

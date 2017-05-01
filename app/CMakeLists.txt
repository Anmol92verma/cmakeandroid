# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

set(distribution_DIR ${CMAKE_SOURCE_DIR}/../distribution)

add_library(crypto STATIC IMPORTED)
set_target_properties(crypto
  PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/lib/${ANDROID_ABI}/libcrypto.a)

add_library(ssl STATIC IMPORTED)
set_target_properties(ssl
  PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/lib/${ANDROID_ABI}/libssl.a)

add_library(curl STATIC IMPORTED)
set_target_properties(curl
  PROPERTIES IMPORTED_LOCATION ${distribution_DIR}/lib/${ANDROID_ABI}/libcurl.a)


include_directories(curl
                    ${distribution_DIR}/include/curl/${ANDROID_ABI})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -lz")


add_library(native-lib SHARED
            src/main/cpp/native-lib.cpp)

set_target_properties(native-lib PROPERTIES
                      LIBRARY_OUTPUT_DIRECTORY ${distribution_DIR}/lib/${ANDROID_ABI})

target_link_libraries(native-lib
                      android
                      curl
                      ssl
                      crypto
                      log)

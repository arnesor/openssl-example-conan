project(openssl-example-conan CXX)
cmake_minimum_required(VERSION 3.1.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
else()
    message(FATAL_ERROR "You need to run conan install <source-dir> in the build-directory \
            first in order to install third-party libraries and generate conanbuildinfo.cmake.")
endif()

find_package(GTest REQUIRED)

add_library(OpensslWrapper OpensslWrapper.cpp)
target_link_libraries(OpensslWrapper CONAN_PKG::OpenSSL)

add_executable(openssl-example main.cpp)
target_link_libraries(openssl-example CONAN_PKG::OpenSSL)

add_executable(openssl-test OpensslWrapperTest.cpp)
target_link_libraries(openssl-test OpensslWrapper GTest::GTest GTest::Main)


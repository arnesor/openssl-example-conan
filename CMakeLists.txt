project(openssl-example-conan CXX)
cmake_minimum_required(VERSION 3.1.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Download conan.cmake automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

find_package(GTest REQUIRED)

add_library(OpensslWrapper OpensslWrapper.cpp)
target_link_libraries(OpensslWrapper CONAN_PKG::OpenSSL)

add_executable(openssl-example main.cpp)
target_link_libraries(openssl-example CONAN_PKG::OpenSSL)

add_executable(openssl-test OpensslWrapperTest.cpp)
target_link_libraries(openssl-test OpensslWrapper GTest::GTest GTest::Main)


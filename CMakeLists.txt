project(openssl-example-conan)
cmake_minimum_required(VERSION 3.1.2)
add_definitions("-std=c++11")


if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
else()
    message(FATAL_ERROR "You need to run conan install <source-dir> in the build-directory \
            first in order to install third-party libraries and generate conanbuildinfo.cmake.")
endif()

add_executable(openssl-example main.cpp)
target_link_libraries(openssl-example CONAN_PKG::OpenSSL)
#target_link_libraries(openssl-example ${CONAN_LIBS})

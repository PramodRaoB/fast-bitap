cmake_minimum_required(VERSION 3.22)
project(fast_bitap)

set(CMAKE_CXX_STANDARD 14)

add_executable(bitap_base
        bitap_base.cpp helper.cpp)

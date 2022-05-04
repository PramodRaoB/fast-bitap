#cmake_minimum_required(VERSION 3.22)
project(fast_bitap)

set(CMAKE_CXX_STANDARD 14)

add_executable(bitap_base
        bitap_base.cpp helper.cpp)

add_executable(bitap_flipped
        bitap_flipped.cpp helper.cpp)

add_executable(bitap_dp
        bitap_dp.cpp helper.cpp)

#cmake_minimum_required(VERSION 3.22)
project(fast_bitap)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -fopenmp-simd -fopenmp -mavx512f -DBUILD")

if (BASE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBASE")
elseif (FLIP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DFLIP")
elseif(DP)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDP")
endif ()

add_executable(bitap driver.cpp bitap_base.cpp bitap_flipped.cpp bitap_dp.cpp helper.cpp)
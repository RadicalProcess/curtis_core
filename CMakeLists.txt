cmake_minimum_required(VERSION 3.10)
project(CurtisCore)

add_library(CurtisCore
        source/Curtis.cpp)

target_include_directories(CurtisCore
        PRIVATE include/curtis_core
        PUBLIC include)

target_compile_features(CurtisCore
        PUBLIC cxx_std_17)

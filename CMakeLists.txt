cmake_minimum_required(VERSION 3.10)
project(CurtisCore)

add_subdirectory(dependencies)

add_library(CurtisCore
        source/Buffer.cpp
        source/SegmentBank.cpp
        source/SegmentDetector.cpp
        source/Granulator.cpp
        source/Curtis.cpp)

target_include_directories(CurtisCore
        PRIVATE include/curtis_core
        PUBLIC include)

target_compile_features(CurtisCore
        PUBLIC cxx_std_17)

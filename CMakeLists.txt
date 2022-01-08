cmake_minimum_required(VERSION 3.10)
project(CurtisCore)

add_subdirectory(dependencies)
add_subdirectory(test)
add_subdirectory(mock)

add_library(CurtisCore
        source/Buffer.cpp
        source/Factory.cpp
        source/SegmentBank.cpp
        source/SegmentDetector.cpp
        source/Granulator.cpp
        source/Curtis.cpp)

add_library(rp::CurtisCore ALIAS CurtisCore)

target_include_directories(CurtisCore
        PRIVATE include/curtis_core
        PUBLIC include)



target_compile_features(CurtisCore
        PUBLIC cxx_std_17)

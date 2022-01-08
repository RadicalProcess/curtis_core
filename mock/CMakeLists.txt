cmake_minimum_required(VERSION 3.15)

add_library(CurtisCore_mock INTERFACE)

add_library(rp::CurtisCore_mock ALIAS CurtisCore_mock)

target_include_directories(CurtisCore_mock
        INTERFACE include)



add_executable(CurtisCoreTestHost
        source/BufferTestCase.cpp
        source/CurtisTestCase.cpp
        source/FactoryTestCase.cpp
        source/GranulatorTestCase.cpp
        source/PolarityTestCase.cpp
        source/SegmentBankTestCase.cpp
        source/SegmentDetectorTestCase.cpp
        )

target_link_libraries(CurtisCoreTestHost
        PRIVATE
        rp::CurtisCore
        rp::CurtisCore_mock
        gmock
        gmock_main)

target_compile_features(CurtisCoreTestHost PRIVATE cxx_std_17)


add_executable(CurtisCoreTestHost
        source/BufferTestCase.cpp
        source/CurtisTestCase.cpp
        source/DensityTestCase.cpp
        source/FactoryTestCase.cpp
        source/GranulatorTestCase.cpp
        source/GlissonTestCase.cpp
        source/PannerTestCase.cpp
        source/PolarityTestCase.cpp
        source/RandomRangeTestCase.cpp
        source/RandomizerTestCase.cpp
        source/CounterTestCase.cpp
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

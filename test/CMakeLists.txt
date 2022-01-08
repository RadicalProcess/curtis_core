
add_executable(CurtisCoreTestHost
        source/FactoryTestCase.cpp
        source/GranulatorTestCase.cpp
        source/SegmentBankTestCase.cpp
        source/SegmentDetectorTestCase.cpp
        )

target_link_libraries(CurtisCoreTestHost
        PRIVATE
        rp::CurtisCore
        gmock
        gmock_main)

target_compile_features(CurtisCoreTestHost PRIVATE cxx_std_17)

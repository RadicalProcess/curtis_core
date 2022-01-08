
add_executable(CurtisCoreTestHost
        PRIVATE
        source/GranulatorTestCase.cpp
        source/SegmentBankTestCase.cpp
        source/SegmentDetectorTestCase.cpp
        )

target_link_libraries(CurtisCoreTestHost
        PRIVATE
        gmock::gmock)

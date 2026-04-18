include("${_build_cmake_local}")

add_library(${PISUBMARINE_MODULE_NAME}.Mock INTERFACE
        PiSubmarine/Telemetry/Api/ISourceMock.h)
target_include_directories(${PISUBMARINE_MODULE_NAME}.Mock INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
PiSubmarineInitTarget(${PISUBMARINE_MODULE_NAME}.Mock)
target_link_libraries(${PISUBMARINE_MODULE_NAME}.Mock INTERFACE ${PISUBMARINE_MODULE_NAME})

find_package(GTest)
target_link_libraries(${PISUBMARINE_MODULE_NAME}.Mock INTERFACE GTest::gtest_main GTest::gmock_main)

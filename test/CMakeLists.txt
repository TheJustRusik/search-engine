cmake_minimum_required (VERSION 3.24)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SrcFiles
        ${MY_SRC_DIR}/Engine.cpp
        ${MY_SRC_DIR}/Jsoner.cpp
        ${MY_SRC_DIR}/Logger.cpp
        ${MY_SRC_DIR}/Storage.cpp
        ${MY_SRC_DIR}/inlcudes.cpp
        )

set(TestsFiles
        Engine_test.cpp
        Jsoner_test.cpp
        Logger_test.cpp
        Storage_test.cpp
        )

add_executable(GtestTests ${TestsFiles} ${SrcFiles})
target_link_libraries(GtestTests nlohmann_json::nlohmann_json GTest::gtest_main)
include(GoogleTest)
target_include_directories(GtestTests PUBLIC ${MY_INCLUDE_DIR})
gtest_discover_tests(GtestTests)

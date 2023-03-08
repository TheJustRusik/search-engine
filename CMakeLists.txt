cmake_minimum_required(VERSION 3.24)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(SearchEngine src/main.cpp includes/includes.h includes/Engine.h includes/Searcher.h includes/Logger.h includes/Storage.h src/Storage.cpp src/inlcudes.cpp src/Engine.cpp src/Logger.cpp src/Searcher.cpp includes/Jsoner.h src/Jsoner.cpp includes/Jsoner.h src/Jsoner.cpp)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

target_link_libraries(SearchEngine PRIVATE nlohmann_json::nlohmann_json)

cmake_minimum_required(VERSION 3.24)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(SearchEngine main.cpp headers/includes.h headers/Engine.h headers/Searcher.h headers/Logger.h headers/Storage.h Storage.cpp inlcudes.cpp Engine.cpp Logger.cpp Searcher.cpp)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(SearchEngine PRIVATE nlohmann_json::nlohmann_json)

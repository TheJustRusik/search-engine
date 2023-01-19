cmake_minimum_required(VERSION 3.24)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 23)

add_executable(SearchEngine src/main.cpp includes/includes.h includes/Engine.h includes/Searcher.h includes/Logger.h includes/Storage.h src/Storage.cpp src/inlcudes.cpp src/Engine.cpp src/Logger.cpp src/Searcher.cpp)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(SearchEngine PRIVATE nlohmann_json::nlohmann_json)

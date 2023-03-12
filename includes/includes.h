#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <filesystem>
#include <thread>
#include <ctime>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#endif

using std::cout;
using std::cerr;
using std::string;
using std::cin;
using std::vector;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::tuple;
using std::pair;
using json = nlohmann::json;

struct StringAndNum {
    string word;
    int num;
};

string fileToString(const string& path);
bool getWord(string& line, string& word, char delim1 = ' ', char delim2 = '\n');


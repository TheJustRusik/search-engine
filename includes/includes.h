//
// Created by TheJustRusik on 13.01.2023.
//

#ifndef SEARCHENGINE_INCLUDES_H
#define SEARCHENGINE_INCLUDES_H

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

using std::cout;
using std::cerr;
using std::string;
using std::cin;
using std::vector;
using std::endl;
using std::ofstream;
using std::ifstream;

using json = nlohmann::json;

struct StringAndNum {
    string word;
    int num;
};

struct Answer{
    vector<int> docIdArr;
    vector<float> relArr;
};

string fileToString(const string& path);
bool getWord(string& line, string& word, char delim1 = ' ', char delim2 = '\n');

#endif //SEARCHENGINE_INCLUDES_H

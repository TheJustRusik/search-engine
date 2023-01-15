//
// Created by TheJustRusik on 13.01.2023.
//

#ifndef SEARCHENGINE_SEARCHER_H
#define SEARCHENGINE_SEARCHER_H

#include "includes.h"
#include "Logger.h"

struct Srch{
    string fileName;
    vector<StringAndNum> freq;
    float abs = 0;
    float rel = -1;
};

class Searcher {
    string dbPath;
    Logger* logger;
    vector<Srch> resultList;

    void bubbleSort();

    static string fixWord(string word);
    bool fileExist(const string& file);
    int findFilePos(const string& file);
    static string parseDbLine(string line, int id, char delim = '~');
public:
    Searcher(char* path, Logger& logger);
    Answer search(vector<string> keyWords, int responses);
};

#endif //SEARCHENGINE_SEARCHER_H

#pragma once

#include "includes.h"
#include "Logger.h"


class Storage : public Logger{
    int docID;
    string dbPath = ".files/";//path for backup of fileName.txt
    unordered_map<string, int> words;//with this vector our program can represent content of fileName.txt
    vector<tuple<int, string ,time_t>>& filesInfo;
    std::mutex& fileWork;
    time_t fileTimeNow;


    //basic functions
    bool haveWord(const string& word);
    int findWordNum(const string& word);
    static bool isUsefulWord(const string& word);
    static string fixWord(string word);

    //important functions with action logging
    void readFile(const string& path);
    void readDB();
    void writeToDB(const string& path);


    static time_t getFileTime(const string& path);

public:
    Storage(const string &filePath, time_t fileTime, int id, std::mutex &mtx, vector<tuple<int, string ,time_t>> &filesInfo);
    int findWords(const vector<string>& word);
    int getDocID() const;
};


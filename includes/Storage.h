#ifndef SEARCHENGINE_STORAGE_H
#define SEARCHENGINE_STORAGE_H

#include "includes.h"
#include "Logger.h"

class Storage {
    string docID;
    string dbPath = ".files/db.txt";//path for db.txt ("heart" of this program)
    string db1Path;//path for backup of fileName.txt
    vector<StringAndNum> words;//with this vector our program can represent content of fileName.txt
    Logger* logger;//object for logging actions of this program. Can tell what is wrong

    //basic functions
    bool haveWord(const string& word);
    int findWordNum(const string& word);
    static bool isUsefulWord(const string& word);
    static string fixWord(string word);
    static string fixLine(string line);
    static string getFileName(string path);

    //important functions with action logging
    void readFile(const string& path);
    void readFromDB(const string& key);
    void writeToDB(const string& key);
    void clearDB(string key);


public:
    Storage(const string& filePath, Logger& logger, int docID);

    void print();
};

#endif //SEARCHENGINE_STORAGE_H

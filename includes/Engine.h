//
// Created by TheJustRusik on 13.01.2023.
//

#ifndef SEARCHENGINE_ENGINE_H
#define SEARCHENGINE_ENGINE_H

#include "includes.h"
#include "Storage.h"
#include "Searcher.h"
#include "Logger.h"

class Engine {
    vector<Storage*> storages1;
    vector<Storage*> storages2;

    std::mutex fileWork;

    vector<string> dirsPaths;
    vector<string> filesPaths;
    vector<string> searchWords;
    vector<string> extensions;
    nlohmann::json answerJson;
    Logger* logger;

    string name;
    string version;
    int maxResponses;
public:
    Engine(Logger& logger);
    void find(bool isUsingRequestsJson, int counter = 0);
    void work();
    void giveTask(int pos1, int pos2, vector<Storage*> storage);
    void getFilesFromDir(const string& initialDir, vector<string>& result, bool isWhiteList);
    bool isInExtensions(const std::string &word);
};

#endif //SEARCHENGINE_ENGINE_H

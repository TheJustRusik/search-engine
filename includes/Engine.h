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
    vector<Storage*> storages;
    vector<string> filesPaths;
    vector<string> searchWords;

    nlohmann::json answerJson;
    Logger* logger;

    string name;
    string version;
    int maxResponses;
public:
    Engine(Logger& logger);
    void find(bool isUsingRequestsJson, int counter = 0);
    void work();

};

#endif //SEARCHENGINE_ENGINE_H

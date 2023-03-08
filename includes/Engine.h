//
// Created by TheJustRusik on 13.01.2023.
//

#ifndef SEARCHENGINE_ENGINE_H
#define SEARCHENGINE_ENGINE_H

#include "includes.h"
#include "Storage.h"
#include "Searcher.h"
#include "Logger.h"
#include "Jsoner.h"

class Engine : public Jsoner{
    vector<Storage*> storages;
    vector<std::thread> threads;
    std::mutex fileWork;
    void threadWorker(vector<pair<string, int>> path);
    void fillStorages();


public:
    Engine();
    void work();
};

#endif //SEARCHENGINE_ENGINE_H

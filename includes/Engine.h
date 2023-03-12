#pragma once

#include "includes.h"
#include "Storage.h"
#include "Logger.h"
#include "Jsoner.h"

class Engine : public Jsoner {
    vector<Storage *> storages;
    vector<std::thread> threads;
    std::mutex fileWork;

    void threadFill(const vector<pair<string, int>> &path);

    void threadFind();

public:
    Engine();

    ~Engine();

    void findWords();

    void fillStorages();
};


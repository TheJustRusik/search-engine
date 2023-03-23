#pragma once

#include "includes.h"
#include "Storage.h"
#include "Logger.h"
#include "Jsoner.h"

class Engine : public Jsoner {
    int maxLoading{};
    int currLoading{};


    vector<Storage *> storages;
    vector<std::thread> threads;
    std::mutex fileWork;

    void threadFill(const vector<tuple<int, string, time_t>>& path);

    void threadFind();

    static string vecToString(const vector<string>& vec);



public:
    Engine();

    ~Engine();

    void findWords();

    void fillStorages();
};


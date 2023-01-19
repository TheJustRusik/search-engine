//
// Created by TheJustRusik on 13.01.2023.
//

#ifndef SEARCHENGINE_LOGGER_H
#define SEARCHENGINE_LOGGER_H
#include "includes.h"

class Logger {
    string path;
public:
    explicit Logger(string path = "");
    ~Logger();
    void newLog(const string& message);
};
#endif //SEARCHENGINE_LOGGER_H

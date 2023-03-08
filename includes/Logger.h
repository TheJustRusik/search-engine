//
// Created by TheJustRusik on 13.01.2023.
//

#ifndef SEARCHENGINE_LOGGER_H
#define SEARCHENGINE_LOGGER_H
#include "includes.h"

class Logger {
    string path;
public:
    Logger(string path = "");
    void newLog(const string& message, short level = 1);
    void startLog();
    void endLog();
};
#endif //SEARCHENGINE_LOGGER_H

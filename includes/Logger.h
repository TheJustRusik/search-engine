#pragma once

#include "includes.h"

class Logger {
    string path;
public:
    Logger(string path = "");
    void newLog(const string& message, short level = 1);
    void startLog();
    void endLog();
};

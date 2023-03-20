#include "Logger.h"
#include "Engine.h"

int main(){

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    auto* logger = new Logger;
    logger->startLog();
    delete logger;

    auto* engine = new Engine;
    engine->findWords();
    delete engine;

}
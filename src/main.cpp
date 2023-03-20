#include "Logger.h"
#include "Engine.h"

int main(){

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    auto* a = new Logger();
    a->startLog();
    delete(a);

    Engine engine;
    engine.findWords();
}
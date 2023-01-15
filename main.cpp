#include "headers/Logger.h"
#include "headers/Engine.h"

int main([[maybe_unused]] int argc, char* argv[]){
    Logger logger(argv[0]);
    Engine a("conf.json", logger, argv[0]);
    a.work();
    system("pause");
}

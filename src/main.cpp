#include "../includes/Logger.h"
#include "../includes/Engine.h"

int main(int argc, char* argv[]){
    Logger logger(argv[0]);
    Engine a("conf.json", logger, argv[0]);
    a.work();
}

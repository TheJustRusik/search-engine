#include "../includes/Logger.h"
#include "../includes/Engine.h"

int main(){
    Logger logger;
    Engine engine(logger);
    engine.work();
}

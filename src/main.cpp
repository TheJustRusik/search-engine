#include "../includes/Logger.h"
#include "../includes/Engine.h"

int main(){
    Logger logger;
    Engine a(logger);
    a.work();
}

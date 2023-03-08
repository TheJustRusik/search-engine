#include "../includes/Engine.h"

Engine::Engine() {
    threads.resize(threadsNum);
}

void Engine::work() {

}

void Engine::fillStorages() {
    vector<vector<pair<string, int>>> pathsForThreads;
    pathsForThreads.resize(threadsNum);

    int iter = 0, id = 0;
    for(const auto& path : filesPaths){
        pathsForThreads[iter].emplace_back(path, id);
        iter = iter + 1 < threadsNum ? iter + 1 : 0;
        id++;
    }

}

void Engine::threadWorker(vector<pair<string, int>> path) {

}

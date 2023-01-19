#include "../includes/Engine.h"

Engine::Engine(const string& configPath, Logger& logger, char* path) {
    this->path = path;
    this->configPath = configPath;
    this->logger = &logger;
    nlohmann::json config;
    ifstream configFile(configPath);
    try {
        if (not configFile.is_open())
            throw std::exception();
    }catch (...){
        cout<<"ERROR: no config file aka \"conf.json\"!\n";
        system("pause");
        exit(EXIT_FAILURE);
    }
    configFile >> config;

    try {
        filesPaths = config["files"];
        if(filesPaths.empty())
            throw std::exception();
    }catch (...){
        cout<<"ERROR: no files in config!\n";
        system("pause");
        exit(EXIT_FAILURE);
    }
    try {
        name = config["config"]["name"];
    }catch (...){
        cout<<"ERROR: no name in config!\n";
        system("pause");
        exit(EXIT_FAILURE);
    }
    try{
        version = config["config"]["version"];
    }catch (...){
        cout<<"ERROR: no version in config!\n";
        system("pause");
        exit(EXIT_FAILURE);
    }
    try{
        maxResponses = config["config"]["max_responses"];
    }catch (...){
        cout<<"WARN: no max_responses in config! Default value will be 5.\n";
        maxResponses = 5;
    }


    cout << "Search engine by TheJustRusik\n";
    cout << name << " config version: " << version << '\n';
    cout << "File's list: \n";
    for (const auto& i : filesPaths)
        cout << i << endl;
}

void Engine::find(bool isUsingRequestsJson, int counter) {
    for (int i = 0; i < filesPaths.size(); i++)
        storages.push_back(new Storage(path, filesPaths[i], *logger, i));
    Searcher searcher(path, *logger);
    Answer answer = searcher.search(searchWords, maxResponses);
    for(int i = 0; i < answer.relArr.size(); i++){
        cout<<"Score (0-worst/1-best): "<<answer.relArr[i]<<" File: "<<filesPaths[answer.docIdArr[i]]<<endl;
    }
    if(isUsingRequestsJson) {
        for(int i = 0; i < answer.relArr.size(); i++){
            answerJson["answer"]["request_" + std::to_string(counter)]["Top-" + std::to_string(i + 1)]["file"] = filesPaths[answer.docIdArr[i]];
            answerJson["answer"]["request_" + std::to_string(counter)]["Top-" + std::to_string(i + 1)]["rel"] = answer.relArr[i];
        }
    }
}

void Engine::work() {
    nlohmann::json config;
    ifstream configFile(configPath);
    configFile >> config;

    if (config["config"]["use_requests.json"]) {
        string reqPath = path;
        while(reqPath[reqPath.size() - 1] != '\\')
            reqPath.pop_back();
        reqPath += "requests.json";
        ifstream reqFile(reqPath);
        nlohmann::json req;
        reqFile >> req;
        vector<string> tempLines = req["requests"];

        int c = 1;

        for(auto i : tempLines) {
            string tempWord;
            while (getWord(i, tempWord))
                searchWords.emplace_back(tempWord);
            cout << "Words to search:\n";
            for (const auto& j : searchWords)
                cout << j << ' ';
            cout<<endl;
            this->find(true, c);
            searchWords.clear();
            c++;
        }
        answerPath = path;
        while (answerPath[answerPath.size() - 1] != '\\')
            answerPath.pop_back();
        answerPath += "answer.json";
        ofstream answerFile(answerPath);
        answerFile << answerJson;
        answerFile.close();
    }
    else {
        cout << "Enter the words to be found separated by a space, press enter to stop: \n";
        string temp;
        while (cin >> temp) {
            if (cin.peek() == '\n')
                cin.clear(std::ios::eofbit);
            searchWords.push_back(temp);
        }
        cout << "Words to search:\n";
        for (const auto& i : searchWords)
            cout << i << ' ';
        cout << endl;
        this->find(false);
    }
}

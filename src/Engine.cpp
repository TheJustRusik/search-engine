#include "../includes/Engine.h"

void Engine::getFilesFromDir(const string &initialDir, vector<string> &result, bool whiteListMode) {
    if (!std::filesystem::exists(initialDir)) {
        cerr<<"Directory not found at the specified address!";
        exit(EXIT_FAILURE);
    }
    vector<string> dirs {initialDir};
    while(not dirs.empty()) {
        for (const auto &obj: std::filesystem::directory_iterator(dirs[0]))
            if (std::filesystem::is_directory(obj))
                dirs.emplace_back(obj.path());
            else if(not extensions.empty()) {
                if (whiteListMode and isInExtensions(obj.path().extension()))
                    result.emplace_back(obj.path());
                else if ((not whiteListMode) and (not isInExtensions(obj.path().extension())))
                    result.emplace_back(obj.path());
            }else
                result.emplace_back(obj.path());

        dirs.erase(dirs.begin());
    }

}

bool Engine::isInExtensions(const std::string &word) {
    for(const auto& ext : extensions)
        if(ext == word)
            return true;
    return false;
}

Engine::Engine(Logger& logger) {
    this->logger = &logger;
    nlohmann::json config;
    ifstream configFile("conf.json");
    try {
        if (not configFile.is_open())
            throw std::exception();
    }catch (...){
        cout<<"ERROR: no config file aka \"conf.json\"!\n";
        exit(EXIT_FAILURE);
    }
    configFile >> config;

    try{
        dirsPaths = config["directories"];
    }catch (...){
        logger.newLog("No directories in conf.json!");
    }
    try{
        extensions = config["extensions"];
    }catch (...){
        logger.newLog("No extensions in conf.json");
    }


    try {
        filesPaths = config["files"];
    }catch (...){
        logger.newLog("No files in conf.json!");
    }
    if(not dirsPaths.empty()){
        bool whiteListMode = true;
        try{
            if(config["config"]["extensions_mode"] == "whitelist")
                whiteListMode = true;
            else
                whiteListMode = false;
        }catch (...){
            logger.newLog("extensions_mode are not exist in conf.json");
        }
        for(const auto& path : dirsPaths)
            getFilesFromDir(path, filesPaths, whiteListMode);

    }
    if(filesPaths.empty()){
        cerr<<"There is not a single existing file with which the program could work. "
              "Check that the data in conf.json ->files && ->directories is correct. Also check "
              "the latest logs for more information. ";
        exit(EXIT_FAILURE);
    }

    try {
        name = config["config"]["name"];
    }catch (...){
        cout<<"ERROR: no name in config!\n";
        exit(EXIT_FAILURE);
    }
    try{
        version = config["config"]["version"];
    }catch (...){
        cout<<"ERROR: no version in config!\n";
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
    if(filesPaths.size() > 1){
        logger->newLog("Working with threads!");
        std::thread first_thread(&Engine::giveTask, this, 0, filesPaths.size() / 2, storages1);
        std::thread second_thread(&Engine::giveTask, this, filesPaths.size() / 2, filesPaths.size(), storages2);
        first_thread.join();
        second_thread.join();
        logger->newLog("Fin working with threads!");
    }else{
        storages1.emplace_back(new Storage(filesPaths[0], *logger, 0, fileWork));
    }

    Searcher searcher(*logger);
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
    ifstream configFile("conf.json");
    configFile >> config;

    if (config["config"]["use_requests.json"]) {
        string reqPath = "requests.json";
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
        string answerPath = "answer.json";
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

void Engine::giveTask(int pos1, int pos2, vector<Storage*> storage) {
    for (; pos1 < pos2; pos1++) {
        storage.emplace_back(new Storage(filesPaths[pos1], *logger, pos1, fileWork));
    }
    std::stringstream temp;
    temp << std::this_thread::get_id();
    logger->newLog("fin work on thread=" + temp.str());
}

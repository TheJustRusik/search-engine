#include "../includes/Jsoner.h"

Jsoner::Jsoner() {
    ifstream configFile("conf.json");
    if(not configFile.is_open()){
        cerr<<"Missing settings file: \"conf.json\"! Create it in the same directory as SearchEngine itself.\n";
        newLog("Missing conf.json");
        endLog();
        exit(EXIT_FAILURE);
    }

    configFile >> config;

    try {
        name = config["config"]["name"];
    }catch (...){
        cerr<<"ERROR: no name in config!\n";
        exit(EXIT_FAILURE);
    }
    try{
        version = config["config"]["version"];
    }catch (...){
        cerr<<"ERROR: no version in config!\n";
        exit(EXIT_FAILURE);
    }
    try{
        if(config["config"]["threads"] < 1)
            throw std::exception();
        threadsNum = config["config"]["threads"];
    }catch (...){
        newLog("WARNING: no threads in config or wrong threads num (... < 1)");
        threadsNum = 2;
    }
    try{
        useReqJson = config["config"]["use_requests.json"];
        if(useReqJson){
            ifstream requestsFile("request.json");
            if(requestsFile.is_open()){
                json requests;
                requestsFile >> requests;
                vector<string> temp = requests["requests"];
                searchWords.resize(temp.size());
                string temp_word;
                for(int i = 0; i < temp.size(); i++){
                    while(getWord(temp[i], temp_word))
                        searchWords[i].push_back(temp_word);
                }
            }else{
                cerr<<"ERROR: no requests.json!\n";
                exit(EXIT_FAILURE);
            }
            if(searchWords[0].empty()) {
                cerr << "ERROR: no words in requests.json!\n";
                exit(EXIT_FAILURE);
            }
        }
    }catch (...){
        cerr<<"ERROR: no use_requests.json in config!";
        exit(EXIT_FAILURE);
    }
    try{
        dirsPaths = config["directories"];
    }catch (...){
        newLog("Category \"directories\" in the config - is empty");
    }
    try{
        extensions = config["extensions"];
    }catch (...){
        newLog("Category \"extensions\" in the config - is empty");
    }
    try {
        filesPaths = config["files"];
    }catch (...){
        newLog("Category \"files\" in the config - is empty");
    }
    try{
        maxResponses = config["config"]["max_responses"];
    }catch (...){
        cerr<<"WARN: no max_responses in config The default value will be set: 5\n";
        maxResponses = 5;
    }

    if(not dirsPaths.empty()){
        try{
            if(config["config"]["extensions_mode"] == "whitelist")
                extIsWhiteList = true;
            else
                extIsWhiteList = false;
        }catch (...){
            newLog("extensions_mode are not exist in conf.json");
        }
        for(const auto& path : dirsPaths)
            getFilesFromDir(path, filesPaths, extIsWhiteList);


    }
    if(filesPaths.empty()){
        cerr<<"There is not a single existing file with which the program could work. \n"
              "Check that the data in conf.json ->files && ->directories is correct. Also check \n"
              "the latest logs for more information. \n";
        exit(EXIT_FAILURE);
    }

    std::sort(filesPaths.begin(), filesPaths.end());
    auto last = std::unique(filesPaths.begin(), filesPaths.end());
    filesPaths.erase(last, filesPaths.end());

    cout << "Search engine by TheJustRusik\n";
    cout << name << " config version: " << version << '\n';
    cout << "Search engine ready to work\n";

    //READING OR MAKING filesInfo.json
    ifstream filesInfoFile(".files/filesInfo.json");
    if(filesInfoFile.is_open()){
        json filesInfoJson;
        filesInfoFile >> filesInfoJson;
        filesInfo = filesInfoJson["FilesInfo"];
    }else{
        ofstream createFilesInfo(".files/filesInfo.json");
        createFilesInfo.close();
    }
}

void Jsoner::getFilesFromDir(const string &initialDir, vector<string> &result, bool whiteListMode) {
    if (!std::filesystem::exists(initialDir)) {
        cerr<<"Directory not found at the specified address!";
        exit(EXIT_FAILURE);
    }
    vector<string> dirs {initialDir};
    while(not dirs.empty()) {
        for (const auto &obj: std::filesystem::directory_iterator(dirs[0]))
            if (std::filesystem::is_directory(obj))
                dirs.emplace_back(obj.path().string());
            else if(not extensions.empty()) {
                if (whiteListMode and isInExtensions(obj.path().extension().string()))
                    result.emplace_back(obj.path().string());
                else if ((not whiteListMode) and (not isInExtensions(obj.path().extension().string())))
                    result.emplace_back(obj.path().string());
            }else
                result.emplace_back(obj.path().string());

        dirs.erase(dirs.begin());
    }

}

bool Jsoner::isInExtensions(const std::string &word) {
    for(const auto& ext : extensions)
        if(ext == word)
            return true;
    return false;
}
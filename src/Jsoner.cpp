#include "Jsoner.h"

Jsoner::Jsoner() {
    ifstream configFile("conf.json");
    if(not configFile.is_open()){
        cerr<<"Missing settings file: \"conf.json\"! Create it in the same directory as SearchEngine itself.\n";
        newLog("Missing conf.json");
        endLog();
        exit(EXIT_FAILURE);
    }
    try {
        configFile >> config;
    }catch (...){
        cerr<<"conf.json is empty. Fill it in like in examples (examples/conf.json) !\n";
        newLog("conf.json is empty or in incorrect format");
        endLog();
        exit(EXIT_FAILURE);
    }

    try {
        name = config["config"]["name"];
    }catch (...){
        cerr<<"ERROR: no name in config!\n";
        newLog("ERROR: no name in config!");
        endLog();
        exit(EXIT_FAILURE);
    }
    try{
        version = config["config"]["version"];
    }catch (...){
        cerr<<"ERROR: no version in config!\n";
        newLog("ERROR: no version in config!");
        endLog();
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
            ifstream requestsFile("requests.json");
            if(requestsFile.is_open()){
                json requests;
                requestsFile >> requests;
                vector<string> temp = requests["requests"];
                searchWords.resize(temp.size());
                string temp_word;
                for(int i = 0; i < temp.size(); i++){
                    std::istringstream iss(temp[i]);
                    while(iss >> temp_word)
                        searchWords[i].push_back(temp_word);
                }
            }else{
                cerr<<"ERROR: no requests.json!\n";
                newLog("ERROR: no requests.json!");
                endLog();
                exit(EXIT_FAILURE);
            }
            if(searchWords[0].empty()) {
                cerr << "ERROR: no words in requests.json!\n";
                newLog("ERROR: no words in requests.json!");
                endLog();
                exit(EXIT_FAILURE);
            }
        }
    }catch (...){
        cerr<<"ERROR: no use_requests.json in config!\n";
        newLog("ERROR: no use_requests.json in config!");
        endLog();
        exit(EXIT_FAILURE);
    }
    try{
        dirsPaths = config["directories"];
    }catch (...){
        newLog("Category \"directories\" in the config - is empty");
    }
    try{
        extensions = config["extensions"];
        if(extensions.empty())
            throw std::exception();
    }catch (...) {
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
            if(config["config"]["extensions_mode"] == "whitelist" or config["config"]["extensions_mode"] == "white")
                extIsWhiteList = true;
            else if(config["config"]["extensions_mode"] == "blacklist" or config["config"]["extensions_mode"] == "black")
                extIsWhiteList = false;
            else
                throw std::exception();
        }catch (...) {
            cerr<< "extensions_mode are not exist or broken in conf.json! This field is responsible for files with which"
                   " extensions will be taken from directories, either whitelisted or blacklisted. This only affects files that "
                   "were automatically found from the directories you specify in \"directories\", files that are directly "
                   "specified in \"files\" are not affected. Choose either \"white\"/\"whitelist\" or \"black\"/\"blacklist\". Default mode will be set as: whitelist\n";
            newLog("extensions_mode are not exist in conf.json");
            extIsWhiteList = true;
        }
        for(const auto& path : dirsPaths)
            getFilesFromDir(path, filesPaths, extIsWhiteList);
    }
    //FIX filesPaths (clean up wrong files)
    try {
        if(filesPaths.empty())
            throw std::exception();
        for (auto iter = filesPaths.end() - 1; iter >= filesPaths.begin(); --iter)
            if (not std::filesystem::exists(*iter) or std::filesystem::is_directory(*iter))
                filesPaths.erase(iter);
    }catch(...){
        cerr << "There is not a single existing file with which the program could work.\n";
        newLog("No files to work with them");
        endLog();
        exit(EXIT_FAILURE);
    }


    if(filesPaths.empty()) {
        cerr << "There is not a single existing file with which the program could work. \n"
                "Check that the data in conf.json ->files && ->directories is correct. Also check \n"
                "the latest logs for more information. \n";
        newLog("ERROR: The reason for the error lies in the fact that the directories and/or paths to the files that you specified in conf.json are incorrect, check their correctness.");
        endLog();
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

        //FIX filesInfoFile (clean up non-existent files)

    }else{
        if(not std::filesystem::exists(".files"))
            std::filesystem::create_directory(".files");

        ofstream createFilesInfo(".files/filesInfo.json");
        createFilesInfo.close();
    }


}

void Jsoner::getFilesFromDir(const string &initialDir, vector<string> &result, bool whiteListMode) {
    if (!std::filesystem::exists(initialDir)) {
        cerr<<"Directory not found at the specified address!\n";
        newLog("Directory not found at the specified address!");
        endLog();
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
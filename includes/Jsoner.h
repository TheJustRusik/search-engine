#ifndef SEARCHENGINE_JSONER_H
#define SEARCHENGINE_JSONER_H
#include "includes.h"
#include "Logger.h"

class Jsoner : public Logger{
    string name;
    string version;
    vector<string> dirsPaths;
    json config;

    void getFilesFromDir(const string &initialDir, vector<string> &result, bool whiteListMode);
    bool isInExtensions(const std::string &word);
public:
    vector<string> filesPaths;
    vector<string> extensions;
    int maxResponses;
    bool useReqJson;
    bool extIsWhiteList;
    int threadsNum;
    vector<tuple<int, string ,time_t>> filesInfo;
    vector<vector<string>> searchWords;

    Jsoner();
};


#endif //SEARCHENGINE_JSONER_H

#pragma once

#include "includes.h"
#include "Logger.h"

class Jsoner : public Logger{
    void getFilesFromDir(const string &initialDir, vector<string> &result, bool whiteListMode);
    bool isInExtensions(const std::string &word);

    vector<string> dirsPaths;
public:
    string name;
    string version;
    json config;
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


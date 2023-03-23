#include "Engine.h"

Engine::Engine() {
    fillStorages();

    cout << " ██████╗███████╗ █████╗ ██████╗  █████╗ ██╗  ██╗  ███████╗███╗  ██╗ ██████╗ ██╗███╗  ██╗███████╗\n";
    cout << "██╔════╝██╔════╝██╔══██╗██╔══██╗██╔══██╗██║  ██║  ██╔════╝████╗ ██║██╔════╝ ██║████╗ ██║██╔════╝\n";
    cout << "╚█████╗ █████╗  ███████║██████╔╝██║  ╚═╝███████║  █████╗  ██╔██╗██║██║  ██╗ ██║██╔██╗██║█████╗  \n";
    cout << " ╚═══██╗██╔══╝  ██╔══██║██╔══██╗██║  ██╗██╔══██║  ██╔══╝  ██║╚████║██║  ╚██╗██║██║╚████║██╔══╝  \n";
    cout << "██████╔╝███████╗██║  ██║██║  ██║╚█████╔╝██║  ██║  ███████╗██║ ╚███║╚██████╔╝██║██║ ╚███║███████╗\n";
    cout << "╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚════╝ ╚═╝  ╚═╝  ╚══════╝╚═╝  ╚══╝ ╚═════╝ ╚═╝╚═╝  ╚══╝╚══════╝\n";

}

void Engine::fillStorages() {
    newLog("Filling Storages [threads: " + std::to_string(threadsNum) + "; files: " +
           std::to_string(filesPaths.size()) + "]", 1);

    vector<vector<tuple<int, string, time_t>>> pathsForThreads;

    pathsForThreads.resize(threadsNum);


    int iter = 0, id;
    if(filesInfo.empty()){
        id = 0;
    }else {
        id = get<0>(*std::max_element(filesInfo.begin(), filesInfo.end(),
                                          [](const auto &a, const auto &b) -> bool {
                                              return get<0>(a) < get<0>(b);
                                          })) + 1;
    }

    if(filesInfo.size() < filesPaths.size())
        filesInfo.resize(filesPaths.size());

    for (const auto &path: filesPaths) {
        time_t tempTime = -1;
        int tempID = id;
        for (auto fileInfo: filesInfo)
            if (get<1>(fileInfo) == path) {
                tempTime = get<2>(fileInfo);
                tempID = get<0>(fileInfo);
                break;
            }
        pathsForThreads[iter].emplace_back(tempID, path, tempTime);
        iter = iter + 1 < threadsNum ? iter + 1 : 0;
        if(tempTime == -1)//if file already in filesInfo.json. tempTime will change so id don't should increase
            ++id;
    }

    currLoading = 0;
    maxLoading = filesPaths.size();

    for (auto pathForThread: pathsForThreads)
        threads.emplace_back(&Engine::threadFill, this, pathForThread);

    for (auto &th: threads)
        if (th.joinable())
            th.join();


    ofstream filesInfoFile(".files/filesInfo.json");
    json filesInfoJson;
    filesInfoJson["FilesInfo"] = filesInfo;
    filesInfoFile << filesInfoJson;
    filesInfoFile.close();

    threads.clear();
    newLog("Successfully", 1);
}

void Engine::threadFill(const vector<tuple<int, string, time_t>>& path) {
    for (const auto &p: path) {
        storages.push_back(new Storage(get<1>(p), get<2>(p), get<0>(p), fileWork, filesInfo));

        fileWork.lock();
        ++currLoading;
        cout << "Loading files: " << currLoading << "/" << maxLoading << "...\n";
        fileWork.unlock();
    }
}

void Engine::findWords() {
    threads.clear();

    vector<pair<int, int>> result; //result[0] = a|b means file with id a have b overlaps

    if (not useReqJson) {

        searchWords.resize(1);
        cout << "Enter the words to be found separated by a space, press enter to stop: \n";
        string temp;
        while (cin >> temp) {
            if (cin.peek() == '\n')
                cin.clear(std::ios::eofbit);
            searchWords[0].push_back(temp);
        }

        cout << "Words to search:\n";
        for (const auto &word: searchWords[0])
            cout << word << ' ';
        cout << endl;

        for (auto &storage: storages)
            result.emplace_back(storage->getDocID(), storage->findWords(searchWords[0]));


        sort(result.begin(), result.end(),
             [](pair<int, int> a, pair<int, int> b) -> bool { return a.second > b.second; });
        if (result.size() > maxResponses)
            result.resize(maxResponses);
        if (result[0].second == 0) {
            cout << "No match found :(\n";
        } else {
            cout << "Search result (Top - " << maxResponses << "):\n";
            for (int i = 0; i < result.size(); i++) {
                if (result[i].second != 0) {
                    cout << "#" << i + 1 << " Score: " << std::fixed << std::setprecision(5)
                         << static_cast<double>(result[i].second) / static_cast<double>(result[0].second) << ", File: "
                         << get<1>(filesInfo[result[i].first]) << "\n";
                }
            }
        }
    } else {
        std::ofstream answerFile("answer.json");
        json answer;

        int iter = 1;
        for (const auto &request: searchWords) {

            for (int i = 0; i < storages.size(); i++)
                result.emplace_back(storages[i]->getDocID(), storages[i]->findWords(request));


            sort(result.begin(), result.end(),
                 [](pair<int, int> a, pair<int, int> b) -> bool { return a.second > b.second; });

            if (result.size() > maxResponses)
                result.resize(maxResponses);

            string req = "request_" + std::to_string(iter);

            answer[req]["Words"] = request;
            if (result[0].second == 0) {
                answer[req]["Result"] = "No match found :(";
            } else {
                for (int i = 0; i < result.size(); i++) {
                    if (result[i].second != 0) {
                        answer[req]["Result"]["#" + std::to_string(i + 1)]["Score"] = static_cast<double>(result[i].second) / result[0].second;
                        answer[req]["Result"]["#" + std::to_string(i + 1)]["File"] = get<1>(filesInfo[result[i].first]);
                    }
                }
            }

            result.clear();
            iter++;
        }
        answerFile << answer;
        answerFile.close();
    }
}

void Engine::threadFind() {
    //TO-DO: multithreading search
}

Engine::~Engine() {
    for(auto& storage : storages)
        delete storage;

    endLog();
}

string Engine::vecToString(const vector<string>& vec) {
    string a = "Words:";
    for (const auto &i: vec)
        a += (' ' + i);
    return a;
}

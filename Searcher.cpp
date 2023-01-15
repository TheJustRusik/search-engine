#include "headers/Searcher.h"

void Searcher::bubbleSort() {
    if (resultList.empty()) {
        logger->newLog("Problem: vector<Srch> is empty!");
        return;
    }
    if (resultList.size() == 1) {
        return;
    }
    for (int i = 0; i < resultList.size() - 1; i++)
        for (int j = 0; j < resultList.size() - i - 1; j++)
            if (resultList[j].rel < resultList[j + 1].rel)
                std::swap(resultList[j], resultList[j+1]);
}

string Searcher::fixWord(string word) {
    char badThings[4] = { ',', '.', '-', ':' };
    for (auto c : badThings) {
        if (word[word.size() - 1] == c)word.pop_back();
    }
    int i = 0;
    for (auto c : word) {
        if (c >= 65 and c <= 90)word[i] += 32;
        i++;
    }
    return word;
}

bool Searcher::fileExist(const string& file) {
    for (const auto& c : resultList)
        if (c.fileName == file)
            return true;
    return false;
}

int Searcher::findFilePos(const string& file) {
    for (int i = 0; i < resultList.size(); i++)
        if (resultList[i].fileName == file)
            return i;
    logger->newLog("Searcher: could not find <" + file + "> in vector<Srch>...");
    return -1;
}

string Searcher::parseDbLine(string line, int id, char delim) {
    string result;
    for (int i = 0; i <= id; i++)
        getWord(line, result, delim, '\n');
    return result;
}

Searcher::Searcher(char* path, Logger& logger) {
    this->logger = &logger;
    dbPath = path;
    while (dbPath[dbPath.size() - 1] != '\\')
        dbPath.pop_back();
    dbPath += ".files//db.txt";
}

Answer Searcher::search(vector<string> keyWords, int responses) {
    for (auto& w : keyWords)
        w = fixWord(w);


    ifstream file(dbPath);
    string line;
    while (getline(file, line)) {
        string fileName = parseDbLine(line, 0);
        for (const auto& w : keyWords)
            if (w == parseDbLine(line, 1))
                if (fileExist(fileName)) {
                    int pos = findFilePos(fileName);
                    int num = stoi(parseDbLine(line, 2));

                    resultList[pos].fileName = fileName;
                    resultList[pos].abs += (float)num;
                    resultList[pos].freq.push_back({ w, num });
                }else {
                    int num = stoi(parseDbLine(line, 2));

                    resultList.push_back({});
                    resultList[resultList.size() - 1].fileName = fileName;
                    resultList[resultList.size() - 1].abs += num;
                    resultList[resultList.size() - 1].freq.push_back({ w, num });
                }
    }
    float maxAbs = -1;
    for (const auto& i : resultList)
        if (i.abs > maxAbs)
            maxAbs = i.abs;
    for (auto& i : resultList)
        i.rel = i.abs / maxAbs;

    bubbleSort();

    Answer answer;
    for(int i = 0; i < responses and i < resultList.size(); i++){
        answer.docIdArr.emplace_back(stoi(resultList[i].fileName));
        answer.relArr.emplace_back(resultList[i].rel);
    }
    return answer;
}
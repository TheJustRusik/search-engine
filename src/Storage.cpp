#include "Storage.h"


bool Storage::haveWord(const string& word) {
    auto it = words.find(word);
    return !(it == words.end());//false if not in map, true if it is
}

int Storage::findWordNum(const string& word) {
    auto it = words.find(word);
    return it == words.end() ? -1 : it->second;//-1 if word not in map, some num if it is
}

bool Storage::isUsefulWord(const string& word) {
    if (word.size() <= 1)return false;
    std::vector<std::string> badWords = { "the", "in", "at", "on", "to", "out", "by", "for", "an", "is", "of", "or", "and" };
    for (const auto& c : badWords) {
        if (word == c)return false;
    }
    return true;
}

string Storage::fixWord(string word) {
    char badThings[6] = { ',', '.', '-', ':', '/', '\\' };
    for (auto c : badThings) {
        if (word[word.size() - 1] == c)word.pop_back();
    }
    for (auto& c : word) {
        c = (char)tolower(c);
    }
    return word;
}

void Storage::readFile(const string& path) {//read words and their num directly from file (slow)
    fileWork.lock();
    newLog("Start Reading From File...", 2);
    fileWork.unlock();

    std::string text, word;
    text = fileToString(path);
    std::istringstream iss(text);
    while (iss >> word) {
        word = fixWord(word);
        if (isUsefulWord(word)) {
            if (haveWord(word)) {
                words[word]++;
            }
            else {
                words[word] = 1;
            }
        }
    }

    fileWork.lock();
    newLog("Successfully", 2);
    fileWork.unlock();
}

void Storage::readDB() {

    fileWork.lock();
    newLog("Start Reading From DataBase, id: " + std::to_string(docID), 2);
    fileWork.unlock();

    ifstream dbFile(dbPath, std::ios::binary);

    if (dbFile) {
        while (true) {
            StringAndNum word;
            dbFile.read(reinterpret_cast<char*>(&word.num), sizeof(word.num));
            if (!dbFile)
                break;
            size_t len;
            dbFile.read(reinterpret_cast<char*>(&len), sizeof(len));
            word.word.resize(len);
            dbFile.read(word.word.data(), len);
            words[word.word] = word.num;
        }
        dbFile.close();
    }
    fileWork.lock();
    newLog("Successful", 2);
    fileWork.unlock();
}

void Storage::writeToDB(const string& path) {
    fileWork.lock();
    newLog("Writing to DataBase file, id: " + std::to_string(docID), 2);
    fileWork.unlock();

    ofstream dbFile(dbPath, std::ios::binary);

    get<0>(filesInfo[docID]) = docID;
    get<1>(filesInfo[docID]) = path;
    get<2>(filesInfo[docID]) = fileTimeNow;

    if (dbFile) {
        for (const auto& [word, num] : words) {
            dbFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
            size_t len = word.length();
            dbFile.write(reinterpret_cast<const char*>(&len), sizeof(len));
            dbFile.write(word.data(), len);
        }
        dbFile.close();
    }
    fileWork.lock();
    newLog("Successful", 2);
    fileWork.unlock();
}

Storage::Storage(const string &filePath, time_t fileTime, int id, std::mutex &mtx, vector<tuple<int, string ,time_t>> &filesInfo) : fileWork(mtx),
                                                                                                                                    docID(id),
                                                                                                                                    filesInfo(filesInfo)
{
    dbPath += std::to_string(id) + ".db";
    fileTimeNow = getFileTime(filePath);
    if(fileTime == fileTimeNow){
        readDB();
    }else{
        readFile(filePath);
        writeToDB(filePath);
    }

}

time_t Storage::getFileTime(const string& path) {
    return std::chrono::system_clock::to_time_t(
            std::chrono::file_clock::to_sys(
                    std::filesystem::last_write_time(path)
            )
    );
}

int Storage::findWords(const vector<string>& word) {
    int coincidences = 0;


    for(const auto& w : word){
        if(haveWord(w)){
            coincidences += findWordNum(w);
        }
    }

    return coincidences;
}

int Storage::getDocID() const {
    return docID;
}

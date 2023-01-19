#include "../includes/includes.h"

string fileToString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

bool getWord(string& line, string& word, char delim1, char delim2) {
    if (line.empty())return false;
    while (line[0] == delim1 or line[0] == delim2) {
        line.erase(0, 1);
    }
    if (line.empty())return false;
    while (line[line.size() - 1] == delim1 or line[line.size() - 1] == delim2) {
        line.pop_back();
    }
    if (line.empty())return false;
    int i = 0; word = "";
    for (auto c : line) {
        if (c == delim1 or c == delim2)break;
        i++;
    }
    for (int j = 0; j < i; j++) {
        word.push_back(line[j]);
    }
    std::string newLine;
    for (; i < line.size(); i++) {
        newLine.push_back(line[i]);
    }
    line = newLine;
    return true;
}

#include "Logger.h"

Logger::Logger(string path) {//path for Logs.txt file
    this->path = path.empty() ? "Logs.txt" : path[path.size() - 1] == '/' ? (path + "Logs.txt") : (path + "/Logs.txt");
}

void Logger::newLog(const string& message, short level) {
    ofstream logs(path, std::ios_base::app);
    switch (level) {
        case 0: logs << "" + message + '\n'; break;
        case 1: logs << "    " + message + '\n'; break;
        case 2: logs << "        " + message + '\n'; break;
        default:logs << "            " + message + '\n'; break;
    }
    logs.close();
}

void Logger::startLog() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto str = oss.str();
    ofstream logs(this->path, std::ios_base::app);
    logs << "Start of logs.\nCurrent time: " + str + '\n';
    logs.close();
}

void Logger::endLog() {
    ofstream logs(path, std::ios_base::app);
    logs << "End of logs.\n";
    logs.close();
}

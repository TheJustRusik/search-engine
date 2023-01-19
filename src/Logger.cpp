#include "../includes/Logger.h"

Logger::Logger(const string& path) {//path for Logs.txt file
    this->path = path;
    while (this->path[this->path.size() - 1] != '\\')
        this->path.pop_back();
    this->path = this->path + "\\Logs.txt";
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    auto str = oss.str();
    ofstream logs(this->path, std::ios_base::app);
    logs << "Beginning writing logs!!!\nCurrent time: " + str + '\n';
    logs.close();
}

Logger::~Logger() {//when c++ delete object of this class, we can find out
    ofstream logs(path, std::ios_base::app);
    logs << "Ended writing logs!!!\n";
    logs.close();
}

void Logger::newLog(const string& message) {
    ofstream logs(path, std::ios_base::app);
    logs << "    " + message + '\n';
    logs.close();
}

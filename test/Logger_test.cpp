#include "Logger.h"
#include "gtest/gtest.h"

TEST(Logger, Test1){
    auto* log = new Logger;
    log->startLog();
    log->newLog("Stage0", 0);
    log->newLog("Stage1", 1);
    log->newLog("Stage1");
    log->newLog("Stage2", 2);
    log->newLog("Stage3", 3);
    log->newLog("Stage3", 4732);
    log->newLog("Stage3", -152);
    log->endLog();//10 lines should be in test_logs.txt

    std::ifstream logsFile("Logs.txt");
    vector<string> logsLines;
    string line;
    while(std::getline(logsFile, line))
        logsLines.emplace_back(line);

    ASSERT_EQ(logsLines.size(), 10);
    ASSERT_EQ(logsLines[0], "Start of logs.");
    ASSERT_EQ(logsLines[2], "Stage0");
    ASSERT_EQ(logsLines[3], "    Stage1");
    ASSERT_EQ(logsLines[4], "    Stage1");
    ASSERT_EQ(logsLines[5], "        Stage2");
    ASSERT_EQ(logsLines[6], "            Stage3");
    ASSERT_EQ(logsLines[7], "            Stage3");
    ASSERT_EQ(logsLines[8], "            Stage3");
    ASSERT_EQ(logsLines[9], "End of logs.");


    logsFile.close();
    std::filesystem::remove("Logs.txt");
    delete log;
}

TEST(Logger, Test2){
    auto* log = new Logger;
    log->newLog("1");
    int logSize1 = 0, logSize2 = 0;
    ifstream reader("Logs.txt");
    string temp;
    while(std::getline(reader, temp))
        ++logSize1;
    reader.close();
    log->newLog("2");
    reader.open("Logs.txt");

    while(std::getline(reader, temp))
        ++logSize2;
    reader.close();
    ASSERT_EQ(logSize1, 1);
    ASSERT_EQ(logSize2, 2);

    std::filesystem::remove("Logs.txt");
    delete log;
}
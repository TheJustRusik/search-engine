#include "Jsoner.h"
#include "gtest/gtest.h"

TEST(Jsoner, Test1){
    auto* jsoner = new Jsoner;
    ASSERT_EQ(jsoner->name, "TestName1337");
    ASSERT_EQ(jsoner->version, "1.3.3.7");
    ASSERT_EQ(jsoner->threadsNum, 1);
    ASSERT_EQ(jsoner->maxResponses, 8);
    ASSERT_EQ(jsoner->useReqJson, true);
    ASSERT_EQ(jsoner->extIsWhiteList, true);
    ASSERT_EQ(jsoner->filesPaths.size(), 6);
    ASSERT_EQ(jsoner->extensions.size(), 2);

    std::filesystem::remove("Logs.txt");
    std::filesystem::remove(".files/filesInfo.json");
    delete jsoner;
}
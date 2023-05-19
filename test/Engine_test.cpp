#include "Engine.h"
#include "gtest/gtest.h"

TEST(Engine, Test1){
    auto* engine = new Engine;
    engine->findWords();

    json answer;
    ifstream answerFile("answer.json");
    answerFile >> answer;

    ASSERT_EQ(answer["request_1"]["Result"]["#1"]["File"], "files/1.txt");
    ASSERT_EQ(answer["request_1"]["Result"]["#1"]["Score"], 1.0);
    ASSERT_EQ(answer["request_1"]["Result"]["#2"]["File"], "files/3.txt");
    ASSERT_EQ(answer["request_1"]["Result"]["#2"]["Score"], 0.3333333333333333);
    ASSERT_EQ(answer["request_1"]["Result"]["#3"]["File"], "files/2.txt");
    ASSERT_EQ(answer["request_1"]["Result"]["#3"]["Score"], 0.16666666666666666);

    ASSERT_EQ(answer["request_2"]["Result"]["#1"]["File"], "files/2.txt");
    ASSERT_EQ(answer["request_2"]["Result"]["#1"]["Score"], 1.0);
    ASSERT_EQ(answer["request_2"]["Result"]["#2"]["File"], "files/1.txt");
    ASSERT_EQ(answer["request_2"]["Result"]["#2"]["Score"], 0.3333333333333333);
    ASSERT_EQ(answer["request_2"]["Result"]["#3"]["File"], "files/3.txt");
    ASSERT_EQ(answer["request_2"]["Result"]["#3"]["Score"], 0.16666666666666666);

    ASSERT_EQ(answer["request_3"]["Result"]["#1"]["File"], "files/1.yml");
    ASSERT_EQ(answer["request_3"]["Result"]["#1"]["Score"], 1.0);

    ASSERT_EQ(answer["request_4"]["Result"], "No match found :(");

    std::filesystem::remove("Logs.txt");
    std::filesystem::remove(".files/filesInfo.json");
    std::filesystem::remove(".files/0.db");
    std::filesystem::remove(".files/1.db");
    std::filesystem::remove(".files/2.db");
    std::filesystem::remove(".files/3.db");
    std::filesystem::remove(".files/4.db");
    std::filesystem::remove(".files/5.db");
    delete engine;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    int code = RUN_ALL_TESTS();
    std::filesystem::remove(".files");
    return code;
}
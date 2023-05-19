#include "Storage.h"
#include "gtest/gtest.h"

TEST(Storage, Test1){
    string path = "files/1.bad";
    time_t time = -1;
    int id = 0;
    std::mutex mtx;
    vector<tuple<int, string ,time_t>> filesInfo = {{id, path, time}};

    auto* storage = new Storage(path, time, id, mtx, filesInfo);
    ASSERT_EQ(storage->findWords({"bad"}), 7);
    ASSERT_EQ(storage->findWords({"file"}), 3);
    ASSERT_EQ(storage->findWords({"word"}), 0);

    std::filesystem::remove("Logs.txt");
    std::filesystem::remove(".files/0.db");
    delete storage;
}
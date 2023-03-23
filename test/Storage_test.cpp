#include "Storage.h"
#include "gtest/gtest.h"

TEST(Storage, Test1){
    string path = "files/1.bad";
    time_t time = std::chrono::system_clock::to_time_t(
            std::chrono::file_clock::to_sys(
                    std::filesystem::last_write_time(path)
            )
    );
    int id = 1337;
    std::mutex mtx;
    vector<tuple<int, string ,time_t>> filesInfo = {{id, path, time}};

    auto* storage = new Storage(path, time, id, mtx, filesInfo);
    ASSERT_EQ(storage->findWords({"bad"}), 7);
    ASSERT_EQ(storage->findWords({"file"}), 3);
    ASSERT_EQ(storage->findWords({"word"}), 0);

    std::filesystem::remove("Logs.txt");
    delete storage;
}
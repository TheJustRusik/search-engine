# SearchEngine🔎
👽Keyword search engine written in C++. It is necessary that you can find, for example, the desired file by entering the words that should be in the desired file.
# For windows:
You can build it by your self or download a ready-made archive (much easier to download a ready-made archive)

How to download:

1. Download the archive whose name is suitable for your OS
2. Unpack where you want
3. Configure conf.json, you can find a manual on it in examples/Examples.md or [touch me.](https://github.com/TheJustRusik/search-engine/blob/master/examples/EXAMPLES.md)

# For linux:
You can build it by your self or download a ready-made archive

How to download:

1. Download the archive whose name is suitable for your OS
2. Unpack where you want
3. Configure conf.json, you can find a manual on it in examples/Examples.md or [touch me.](https://github.com/TheJustRusik/search-engine/blob/master/examples/EXAMPLES.md)

How to build:

1. Make sure you have CMake (minimum version - 3.24) Git and any C++ compiler that can support C++23
2. Run this command:
    > git clone "https://github.com/TheJustRusik/search-engine"
3. Go to search-engine dir: 
    > cd search-engine 
4. Create build dir: 
    > mkdir build
5. Run this command:
    > cmake ..
6. Run this command:
    > make

In build folder you will have SearchEngine application. After that, take the .files folder and conf.json from the examples folder (you can also take requests.json) and put them next to the SearchEngine application. Set up conf.json, and you can start using the search engine!
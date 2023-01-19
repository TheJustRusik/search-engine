# SearchEngine🔎
👽Keyword search engine written in C++. It is necessary that you can find, for example, the desired file by entering the words that should be in the desired file
how to use?
# For windows:
First you need to install this application. The easiest way to do this is to download the release and unpack it where you need it.
Or you can download the code and compile it yourself.

Next to the .exe there should be at least conf.json aka configuration file in which you will configure the search engine and tell it which files to work with

The .files directory is needed exclusively for the search engine. You don't need to remove it or interact with it in any way.

What is requests.json and answer.json for? 

If you want to make several requests at once, just enter them in requests.json, 
then in conf.json opposite "use_requests.json" check the "true" box, 
then run the program. The answer will be both in the console and in answer.json
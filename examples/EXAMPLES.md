# Examples of conf.json and request.json
There you can see how your conf.json and request.json should look like.

If the program does not work, most likely you made a fingerprint in one of these files, so be careful!

# About conf.json
As you can see, in config you have name, version, threads, max_responses, use_requests.json and extensions_mode

In "name" and "version" you can write anything, it will be shown in console.

"threads" are responsible for how many threads the program will use, I recommend not setting the value higher than the number of your logical processor cores on your system

"max_responses" is responsible for how many files the program will give in response. For example, if a word is found in 10 files, but the "max_responses" is 5, then only the first 5 files will be in the answer (by the number of matches)

"use_requests.json" is responsible for the mode of the program. If its value is false, then you will make the request yourself when you run the program. If its value is true, then the program will receive requests from "request.json" and duplicate the response in "answer.json"

"extensions_mode" is needed if you are adding files via "directories". From the directories specified in "directories", only those files where there extensions are in "extensions" will be taken if the value of "extensions_mode" is in whitelist mode (for this, write whitelist or white). And files with extensions from "extensions" will be ignored if the mode of operation is in the black list (for this, write in front of blacklist or black)

In the "files", specify the full path to the files

All files will be extracted from the folders specified in the "directories". For example, if you specify a certain folder inside which there will be other folders, the program will take files even from them (recursive search)

in "extensions" specify extensions in the following format ".txt" ".yml" ".conf" and so on. (Point required)

# About request.json

In request.json 1 line is a 1 request, where 1 line can contain more than 1 word, It will process this request in the same way as if you entered a few words in the console

Each line is one independent request of each other
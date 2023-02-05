# Examples of conf.json and request.json
In this dir you can see how your conf.json and request.json should look like.

Also, don't forget to add next to executable file ".files" directory with "db.txt" file inside

If the program does not work, most likely you made a fingerprint in one of these files, so be careful!

# About conf.json
As you can see, in config you have name, version, max_responses and use_requests.json

In "name" and "version" you can write anything you want, "max_responses" is responsible for how many responses will be given to your request, "use_requests.json" is responsible for how the request will be made, if false then you will give the request in the console. And if true, then you write your requests to the requests.json file and the program will give an answer in the console and also duplicate the answer to answer.json

# About request.json

In request.json 1 line is a 1 request, where 1 line can contain more than 1 word, It will process this request in the same way as if you entered a few words in the console

Each line is one independent request of each other
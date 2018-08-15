//  Created by Krishna Gudipati on 8/14/18.
//  Copyright © 2018 The Weather Channel. All rights reserved.

#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

const string playlist = "https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/bipbop_4x3_variant.m3u8";

void downloadPlayListItem(const char* url, FILE* outputFile) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, outputFile);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

int main(void)
{
    FILE *outfile;
    outfile = fopen("outfile-new", "w");
    string url = string("https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/gear0/fileSequence176.aac");
    downloadPlayListItem(url.c_str(), outfile);
    return 0;
}

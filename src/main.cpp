//  Created by Krishna Gudipati on 8/14/18.
//  Copyright © 2018 The Weather Channel. All rights reserved.

#include <iostream>
#include <string>
#include <curl/curl.h>

using namespace std;

int main(void)
{
    CURL *curl;
    CURLcode res;
    string readBuffer;
    FILE *outfile;
    outfile = fopen("outfile", "w");

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/bipbop_4x3_variant.m3u8");
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        cout << readBuffer << endl;
    }
    return 0;
}

//  Created by Krishna Gudipati on 8/14/18.

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include <curl/curl.h>


using namespace std;

const string playlistUrl = "https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/bipbop_4x3_variant.m3u8";

void downloadPlayListItem(const char* url);

ofstream hlsstream;

int main(void) {
    hlsstream.open("fileSequence176.aac", ios::out | ios::app | ios::binary);
    if (hlsstream.is_open()) {
        string urlPath = string("https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/gear0/fileSequence176.aac");
        downloadPlayListItem(urlPath.c_str());
    }

    return 0;
}

static size_t curlCallBack(void *curlData, size_t size, size_t receievedSize, void *writeToFileBuffer)
{
    ((string*) writeToFileBuffer)->append((char *) curlData, size * receievedSize);
    return size * receievedSize;
}

void downloadPlayListItem(const char* url) {

    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl != NULL) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallBack);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        hlsstream << readBuffer << endl;
        std::cout << readBuffer << endl;
    }
}

//  HLSPlaylistDownloader.cpp
//
//  Created by Krishna Gudipati on 8/14/18.

#include "HLSPlaylistDownloader.hpp"
#include <curl/curl.h>
#include <iostream>
#include <fstream>

HLSPlaylistDownloader::HLSPlaylistDownloader() {
}

HLSPlaylistDownloader::~HLSPlaylistDownloader() {
}

void HLSPlaylistDownloader::setDownloadInfo(string urlPath, string outfile) {
    url = urlPath;
    outputFile = outfile;
}

bool HLSPlaylistDownloader:: downloadPlaylist() {
    hlsstream = ofstream(outputFile, ios::out | ios::app);
    return downloadItem(url.c_str());
}

bool HLSPlaylistDownloader:: downloadStream() {
    hlsstream = ofstream(outputFile, ios::out | ios::app | ios::binary);
    return downloadItem(url.c_str());
}

size_t HLSPlaylistDownloader::curlCallBack(void *curlData, size_t size, size_t receievedSize, void *writeToFileBuffer)
{
    ((string*) writeToFileBuffer)->append((char *) curlData, size * receievedSize);
    return size * receievedSize;
}

bool HLSPlaylistDownloader::downloadItem(const char* url) {
    
    bool success = false;
    
    if (hlsstream.is_open()) {
        
        CURL *curl;
        CURLcode result = CURL_LAST;
        string readBuffer;
        
        curl = curl_easy_init();
        if (curl != NULL) {
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlCallBack);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            result = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            
            hlsstream << readBuffer << endl;
            //std::cout << readBuffer << endl;
        }
        
        hlsstream.close();
        
        success = (result == 0);
    }
    
    return false;
}

//  HLSPlaylistDownloader.cpp
//
//  Created by Krishna Gudipati on 8/14/18.

#include "HLSPlaylistDownloader.hpp"
#include <curl/curl.h>
#include <iostream>
#include <vector>

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
        }
        
        hlsstream.close();
        
        success = (result == 0);
    }
    
    return success;
}

void HLSPlaylistDownloader::downloadIndividualPlaylist(string baseUrlPath, string playlistPath, string destination) {

    url = baseUrlPath + playlistPath;
    
    vector <string> nameItems;
    stringstream urlStringStream(playlistPath);
    string tmpItem;
    
    while(getline(urlStringStream, tmpItem, '/')) {
        nameItems.push_back(tmpItem);
    }
    
    if (!(nameItems.size() > 0)) {
        return;
    }
    
    string playlistName = nameItems[0];
    string playlistLocalPath = destination + "/" + playlistName;
    int status;
    int success = 0;
    
    string createDirCommand = "mkdir " + playlistLocalPath;
    
    status = system(createDirCommand.c_str());
    if (status != success){
        cout << "ERROR : Not able to create directory : " << endl << playlistLocalPath << ". Provide new directory name" << endl;
        return;
    }
    
    string localDownloadFileName = destination + "/" + playlistPath;
    hlsstream = ofstream(localDownloadFileName, ios::out | ios::app);
    if (downloadItem(url.c_str())) {
        // download sequence files
        ifstream playlistfile(localDownloadFileName, ios::in);
        vector<string> playlistStreams;
        
        if (playlistfile.is_open()) {
            string line;
            while (!playlistfile.eof()) {
                getline(playlistfile, line);
                line.erase(0, line.find_first_not_of("\t\n\v\f\r "));
                if (line.empty() || (line[0] == '#')) {
                    continue;
                }
                playlistStreams.push_back(line);
            }
            playlistfile.close();
        }
        
        if (playlistStreams.size() > 0) {
            for (vector<string>::iterator sequence = playlistStreams.begin(); sequence != playlistStreams.end(); ++sequence) {
                string localDownloadSequenceName = playlistLocalPath + "/" + *sequence;
                url = baseUrlPath + playlistName + "/" + *sequence;
                hlsstream = ofstream(localDownloadSequenceName, ios::out | ios::app | ios::binary);
                downloadItem(url.c_str());
            }
        }
    } 
}

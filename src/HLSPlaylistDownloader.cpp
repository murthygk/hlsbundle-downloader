//
//  HLSPlaylistDownloader.cpp
//  HLSVoDBundleDownloader
//
//  Created by Krishna Gudipati on 8/14/18.
//  Copyright © 2018 The Weather Channel. All rights reserved.
//

#include "HLSPlaylistDownloader.hpp"
#include "HLSPlaylistUtilities.hpp"
#include <curl/curl.h>
#include <iostream>
#include <vector>

HLSPlaylistDownloader::HLSPlaylistDownloader() {
}

HLSPlaylistDownloader::~HLSPlaylistDownloader() {
}


void HLSPlaylistDownloader::setDownloadInfo(string urlPath, string outfile) {
    m_url = urlPath;
    m_outputFile = outfile;
}

bool HLSPlaylistDownloader:: downloadPlaylist() {
    m_hlsstream = ofstream(m_outputFile, ios::out | ios::app);
    return downloadItem(m_url.c_str());
}

bool HLSPlaylistDownloader:: downloadStream() {
    m_hlsstream = ofstream(m_outputFile, ios::out | ios::app | ios::binary);
    return downloadItem(m_url.c_str());
}

size_t HLSPlaylistDownloader::curlCallBack(void *curlData, size_t size, size_t receievedSize, void *writeToFileBuffer)
{
    ((string*) writeToFileBuffer)->append((char *) curlData, size * receievedSize);
    return size * receievedSize;
}

bool HLSPlaylistDownloader::downloadItem(const char* url) {
    
    bool success = false;
    
    if (m_hlsstream.is_open()) {
        
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
            
            m_hlsstream << readBuffer << endl;
        }
        
        m_hlsstream.close();
        
        success = (result == 0);
    }
    
    return success;
}

void HLSPlaylistDownloader::downloadIndividualPlaylist(string baseUrlPath, string playlistPath, string destination) {
    
    m_url = baseUrlPath + playlistPath;
    
    vector <string> nameItems = HLSPlaylistUtilities::tokenize(playlistPath, '/');

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
        cout << "ERROR : Not able to create directory : " << endl << playlistLocalPath << endl;
        return;
    }
    
    string localDownloadFileName = destination + "/" + playlistPath;
    m_hlsstream = ofstream(localDownloadFileName, ios::out | ios::app);
    if (downloadItem(m_url.c_str())) {
        // download streams
        
        vector<string> playlistStreams = HLSPlaylistUtilities::buildList(localDownloadFileName);
        
        if (playlistStreams.size() > 0) {
            for (vector<string>::iterator sequence = playlistStreams.begin(); sequence != playlistStreams.end(); ++sequence) {
                string localDownloadSequenceName = playlistLocalPath + "/" + *sequence;
                m_url = baseUrlPath + playlistName + "/" + *sequence;
                m_hlsstream = ofstream(localDownloadSequenceName, ios::out | ios::app | ios::binary);
                downloadItem(m_url.c_str());
            }
        }
    }
}


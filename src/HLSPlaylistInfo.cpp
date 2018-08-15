//  HLSPlaylistInfo.cpp
//
//  Created by Krishna Gudipati on 8/14/18.

#include "HLSPlaylistInfo.hpp"
#include <regex>

using namespace std;

HLSPlaylistInfo::HLSPlaylistInfo(const string url) {
    completePlaylistUrlPath = url;
    extractPlaylistInfo();
}

HLSPlaylistInfo::~HLSPlaylistInfo() {
}

string HLSPlaylistInfo::getMainPlaylistName() {
    return mainPlaylistName;
}

string HLSPlaylistInfo::getBaseUrlPath() {
    return baseUrlPath;
}

void HLSPlaylistInfo::extractPlaylistInfo() {
    
    vector <string> urlItems;
    stringstream urlStringStream(completePlaylistUrlPath);
    string tmpItem;
    
    while(getline(urlStringStream, tmpItem, '/')) {
        urlItems.push_back(tmpItem);
    }
    
    protocolIdentifier = urlItems[1];
    host = urlItems[2];
    mainPlaylistName = urlItems[urlItems.size() - 1];
    
    // While downloading each playlist item the name of the list/item is appended to this baseUrlPath to form a valid url path for downloading
    baseUrlPath = regex_replace(completePlaylistUrlPath, regex(mainPlaylistName), "");
}

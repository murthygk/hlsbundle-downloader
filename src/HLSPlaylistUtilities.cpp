//  HLSPlaylistUtilities.cpp
//  Created by Krishna Gudipati on 8/15/18.

#include "HLSPlaylistUtilities.hpp"

#include <iostream>

using namespace std;

bool checkForContinuity();

vector<string> HLSPlaylistUtilities::buildList(string infile) {
    
    vector<string> items;
    
    // Build items list from the file
    ifstream playlistfile(infile, ios::in);
    
    if (playlistfile.is_open()) {
        string line;
        while (!playlistfile.eof()) {
            getline(playlistfile, line);
            line.erase(0, line.find_first_not_of("\t\n\v\f\r "));
            if (line.empty() || (line[0] == '#')) {
                continue;
            }
            items.push_back(line);
        }
        
        playlistfile.close();
    }
    
    return items;
}

vector<string> HLSPlaylistUtilities::tokenize(string path, char delimiter) {
    
    vector <string> tokens;
    stringstream urlStringStream(path);
    string tmpItem;
    
    while(getline(urlStringStream, tmpItem, '/')) {
        tokens.push_back(tmpItem);
    }
    
    return tokens;
}

bool HLSPlaylistUtilities::createDirectory(string path) {
    string createDirCommand = "mkdir " + path;
    return system(createDirCommand.c_str());
}

bool HLSPlaylistUtilities::fetchAndvalidateUserInput(string *destinationPath, HLSPlaylistInfo *playlistInfo) {
    
    cout << endl << "                 -----***** HLS Playlist Downloader *****-----                 " << endl;
    cout << endl << "       Please provide hls URL and output directory to save the play list       " << endl << endl;
    
    string urlPath;
    string dirPath;
    
    while (1) {
        
        cout << " Enter HLS Url : ";
        cin >> urlPath;
        
        cout << " Enter output directory : ";
        cin >> dirPath;
        
        if (!playlistInfo->extractPlaylistInfo(urlPath)) {
            cout << "ERROR : "  << urlPath << " is an invalid/corrupted url. Provide new url name" << endl;
            if (checkForContinuity()) {
                continue;
            }
            
            return false;
        }
        
        // Actual play list root directory
        string playListRootDirectory = dirPath + "/" + playlistInfo->getPlaylistRootName();
        if (HLSPlaylistUtilities::createDirectory(playListRootDirectory) != 0){
            cout << "ERROR : Not able to create directory : " << playListRootDirectory << ". Provide new directory name" << endl;
            if (checkForContinuity()) {
                continue;
            }
            
            return false;
        }
        
        *destinationPath = playListRootDirectory;
        
        cout << endl;
        
        return true;
    }
}

bool checkForContinuity() {
    cout << "Press any key + ENTER to continue or `e/E + ENTER` for exit the downloader : " << endl;
    char c;
    cin >> c; 
    
    if ((c == 'e') || (c == 'E')) {
        return false;
    }
    
    cin.clear();
    return true;
}

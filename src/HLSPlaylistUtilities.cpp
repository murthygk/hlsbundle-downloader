//  HLSPlaylistUtilities.cpp
//
//  Created by Krishna Gudipati on 8/15/18.

#include "HLSPlaylistUtilities.hpp"

vector<string> HLSPlaylistUtilities::buildList(string infile) {
    
    vector<string> items;
    
    // Build items from the file
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

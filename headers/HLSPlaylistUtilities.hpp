//  HLSPlaylistUtilities.hpp
//  Created by Krishna Gudipati on 8/15/18.

#ifndef HLSPlaylistUtilities_hpp
#define HLSPlaylistUtilities_hpp

#include "HLSPlaylistInfo.hpp"

#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

class HLSPlaylistUtilities {
    public:
       static vector<string> buildList(string infile);
       static vector<string> tokenize(string path, char delimiter);
       static bool createDirectory(string path);
       static bool fetchAndvalidateUserInput(string *destinationPath, HLSPlaylistInfo *playlistInfo);
};

#endif /* HLSPlaylistUtilities_hpp */

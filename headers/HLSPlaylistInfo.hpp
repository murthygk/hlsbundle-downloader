//  HLSPlaylistInfo.hpp
//
//  Created by Krishna Gudipati on 8/14/18.

#ifndef HLSPlaylistInfo_hpp
#define HLSPlaylistInfo_hpp

#include <sstream>
#include <vector>

using namespace std;

class HLSPlaylistInfo {
    
    public :
        HLSPlaylistInfo(string url);
        ~HLSPlaylistInfo();
    
    private:
        string completePlaylistUrlPath;
        string baseUrlPath;
    
        string protocolIdentifier;
        string host;
        string mainPlaylistName;
    
        void extractPlaylistInfo();
    
    public:
        string getMainPlaylistName();
        string getBaseUrlPath();
};

#endif /* HLSPlaylistInfo_hpp */

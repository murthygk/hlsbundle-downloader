//
//  HLSPlaylistDownloader.hpp
//  HLSVoDBundleDownloader
//
//  Created by Krishna Gudipati on 8/14/18.
//  Copyright © 2018 The Weather Channel. All rights reserved.
//

#ifndef HLSPlaylistDownloader_hpp
#define HLSPlaylistDownloader_hpp

#include <sstream>
#include <fstream>

using namespace std;

class HLSPlaylistDownloader {
    
    public :
    HLSPlaylistDownloader();
    ~HLSPlaylistDownloader();
    
    private:
        string m_url;
        string m_outputFile;
        ofstream m_hlsstream;
    
        bool downloadItem(const char* url);
        static size_t curlCallBack(void *curlData, size_t size, size_t receievedSize, void *writeToFileBuffer);
    
    public:
        void setDownloadInfo(string urlPath, string outfile);
        bool downloadPlaylist();
        bool downloadStream();
        void downloadIndividualPlaylist(string baseUrlPath, string playlistName, string destination);
};

#endif /* HLSPlaylistDownloader_hpp */

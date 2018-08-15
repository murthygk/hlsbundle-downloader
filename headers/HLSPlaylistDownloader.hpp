//  HLSPlaylistDownloader.hpp
//
//  Created by Krishna Gudipati on 8/14/18.

#ifndef HLSPlaylistDownloader_hpp
#define HLSPlaylistDownloader_hpp

#include <sstream>
#include <list>
#include <fstream>

using namespace std;

class HLSPlaylistDownloader {
    
    public :
    HLSPlaylistDownloader();
    ~HLSPlaylistDownloader();
    
    private:
        string url;
        string outputFile;
        ofstream hlsstream;
    
        bool downloadItem(const char* url);
        static size_t curlCallBack(void *curlData, size_t size, size_t receievedSize, void *writeToFileBuffer);
    
    public:
        void setDownloadInfo(string urlPath, string outfile);
        bool downloadPlaylist();
        bool downloadStream();
        bool downloadIndividualPlaylist(string baseUrlPath, string playlistName, string destination);
};

#endif /* HLSPlaylistDownloader_hpp */

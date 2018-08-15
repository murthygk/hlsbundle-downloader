#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>

#include "HLSPlaylistInfo.hpp"
#include "HLSPlaylistDownloader.hpp"

using namespace std;

// https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/gear0/prog_index.m3u8
// https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/gear1/prog_index.m3u8
// https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8
// https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/gear3/prog_index.m3u8
// https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/gear4/prog_index.m3u8

const string playlistRootUrl = "https://devstreaming-cdn.apple.com/videos/streaming/examples/bipbop_4x3/bipbop_4x3_variant.m3u8";

ofstream hlsstream;

int main(void)
{
    HLSPlaylistInfo *playlistInfo = new HLSPlaylistInfo(playlistRootUrl);
    
    // 0.1 Create bundle directory - UserProvided
    // 0.2 Create plalist directory - bipbop_4x3_variant.m3u8
    // 1. Download the root url and save it in this directory - bipbop_4x3_variant.m3u8
    // 2. Parse the file and make a list of items : gear0/prog_index.m3u8, gear1/prog_index.m3u8, gear2/prog_index.m3u8, gear3/prog_index.m3u8, gear4/prog_index.m3u8
    // 3. For each of the itemlist ()                 ^
    // 3.1 Create a directory - gear0
    //    3.1 Concatenate downloadPathBaseurl + item : gear0/prog_index.m3u8
    //    3.2 Dowload the file and save it in this directory
    //    3.3 Parse the file and make a list of streams : fileSequence52.aac, fileSequence53.aac ....
    //    3.2.1 For each of the stream list
    //    3.2.1.1 Download each stream and save in this directory
    //    3.2.1 ForEnd
    // 3. ForEnd
    
    
    int status;
    int success = 0;
    
    // 0 - fetch output directory name from user
    string localBundleDir = "UserProvidedDirectoryName"; // playlistInfo->getMainPlaylistName();
    string createDirCommand = "mkdir " + localBundleDir;
    
    status = system(createDirCommand.c_str());
    if (status != success){
        cout << "ERROR : Not able to create directory : " << endl << localBundleDir << ". Provide new directory name" << endl;
        exit(1);
    }
    
    // Actual play list root directory
    string playListRootDirectory = localBundleDir + "/" + playlistInfo->getMainPlaylistName();
    createDirCommand = "mkdir " + playListRootDirectory;
    status = system(createDirCommand.c_str());
    if (status != success){
        cout << "ERROR : Not able to create directory : " << endl << playListRootDirectory << ". Provide new directory name" << endl;
        exit(1);
    }
    
    // 1 Download the root playlist file
    string localDownloadFileName = playListRootDirectory + "/" + playlistInfo->getMainPlaylistName();
    // string completeUrlPath = playlistInfo->getBaseUrlPath() + playlistInfo->getMainPlaylistName();
    HLSPlaylistDownloader *hlsDownloader = new HLSPlaylistDownloader();
    hlsDownloader->setDownloadInfo(playlistRootUrl, localDownloadFileName);
    if (hlsDownloader->downloadPlaylist()) {
        
    }
    
    playlistInfo = NULL;
    
    return 0;
}

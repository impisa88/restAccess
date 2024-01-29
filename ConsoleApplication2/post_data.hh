#ifndef POST_DATA_HH
#define POST_DATA_HH

#include <string>

class PostData {
private:
    //int id;
    std::string name;
    std::string path;
    std::string systemLinkPath;
    int fkFileType;
    int fkFile;
    //int altitude;
    //int latitude;
    //int longitude;
    float height;
    float azimuth;

public:
    PostData();
    PostData(/*int id,*/const std::string& name, const std::string& path,
        const std::string& systemLinkPath, int fkFileType,
        int fkFile, float azimuth, float height/*int altitude, int latitude, int longitude*/);

    std::string toJsonString() const;

    std::string sendPostData(const char* url, const std::string& accessToken) const;
};

#endif // Post_data_hh
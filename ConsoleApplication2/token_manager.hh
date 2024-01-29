#ifndef TOKEN_MANAGER_HH
#define TOKEN_MANAGER_HH

#include <iostream>
#include <curl/curl.h>
#include <cstring>
#include <map>

class TokenManager {
private:
    CURL* curl;
    std::string responseData;
    std::string accessToken;

    std::map<std::string, std::string> ExtractValuesFromJson(const std::string& jsonString);

public:
    TokenManager();
    ~TokenManager();

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output);
    std::string sendRequest(const char* url, const char* payload);
    void requestToken(const char* url, const char* payload);
    std::string getAccessToken() const;
};

#endif // TOKEN_MANAGER_HH
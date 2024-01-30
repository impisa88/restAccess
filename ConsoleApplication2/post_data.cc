#include "post_data.hh"
#include "token_manager.hh"
#include "curl/curl.h"
#include <sstream>


PostData::PostData()
    : id(0), fkFileType(0), fkFile(0), altitude(0), latitude(0), longitude(0) {}

PostData::PostData(int id, const std::string& name, const std::string& path, const std::string& systemLinkPath, int fkFileType, int fkFile, double altitude, double latitude, double longitude)
    : id(id), name(name), path(path), systemLinkPath(systemLinkPath),
    fkFileType(fkFileType), fkFile(fkFile), altitude(altitude),
    latitude(latitude), longitude(longitude) {}



std::string PostData::toJsonString() const {
    std::ostringstream json;
    json << "{"
        << "\"id\":" << id << ","
        << "\"name\":\"" << name << "\","
        << "\"path\":\"" << path << "\","
        << "\"system_link_path\":\"" << systemLinkPath << "\","
        << "\"fk_file_type\":" << fkFileType << ","
        << "\"fk_file\":" << fkFile << ","
        << "\"altitude\":" << altitude << ","
        << "\"latitude\":" << latitude << ","
        << "\"longitude\":" << longitude
        << "}";
    return json.str();
}


std::string PostData::sendPostData(const char* url, const std::string& accessToken) const {
    CURL* curl = curl_easy_init();
    if (!curl) {
        return "";  // error in curl start
    };

    // postJson posui os dados de PostData
    std::string postJson = toJsonString(); 

    // Configurate a url for a POST request
    curl_easy_setopt(curl, CURLOPT_URL, url);

    // Configurate a data to be send in post request body
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postJson.c_str());

    // Configurar a função de callback para lidar com os dados recebidos
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, TokenManager::WriteCallback);

    // Use a responseData variable that been used in TokenManager class
    std::string responseData;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    // Configurar o cabeçalho de autorização Bearer
    std::string authHeader = "Authorization: Bearer " + accessToken;
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, authHeader.c_str());
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    //Do a Post request
    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);

    if (res != CURLE_OK) {
        fprintf(stderr, "Erro na solicitação POST: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);

    return responseData;
};


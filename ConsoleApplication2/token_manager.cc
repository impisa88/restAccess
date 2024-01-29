#include "token_manager.hh"

TokenManager::TokenManager() : curl(curl_easy_init()) {
    if (curl) {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }
}

TokenManager::~TokenManager() {
    if (curl) {
        curl_easy_cleanup(curl);
        curl_global_cleanup();
    }
}

size_t TokenManager::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

std::map<std::string, std::string> TokenManager::ExtractValuesFromJson(const std::string& jsonString) {
    std::map<std::string, std::string> values;

    std::size_t tokenPosition = jsonString.find("\"access_token\"");
    if (tokenPosition != std::string::npos) {
        std::size_t valuePosition = jsonString.find(":", tokenPosition);
        if (valuePosition != std::string::npos) {
            valuePosition = jsonString.find_first_not_of(" \t\n\r\f\v", valuePosition + 1);
            if (valuePosition != std::string::npos) {
                std::size_t valueEnd = jsonString.find_first_of(",}", valuePosition);
                if (valueEnd != std::string::npos) {
                    std::string token = jsonString.substr(valuePosition, valueEnd - valuePosition);
                    token.erase(std::remove(token.begin(), token.end(), '\"'), token.end());
                    values["access_token"] = token;
                }
            }
        }
    }
    return values;
}

std::string TokenManager::sendRequest(const char* url, const char* payload) {
    if (!curl) {
        return "";  // Falha na inicialização do curl
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "Erro na solicitação: %s\n", curl_easy_strerror(res));
    }

    return responseData;
}

void TokenManager::requestToken(const char* url, const char* payload) {
    responseData = sendRequest(url, payload);

    std::map<std::string, std::string> values = ExtractValuesFromJson(responseData);

    for (const auto& pair : values) {
        accessToken = pair.second;
    }
}

std::string TokenManager::getAccessToken() const {
    return accessToken;
}

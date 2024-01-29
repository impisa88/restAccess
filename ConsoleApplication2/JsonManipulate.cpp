#include <iostream>
#include <curl/curl.h>
#include <cstring> // Para usar std::strtok

// callback function for the receive data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// Function to extract a value of one key in a simple Json
std::string ExtractJsonValue(const std::string& jsonString, const std::string& key) {
    std::size_t keyPosition = jsonString.find("\"" + key + "\"");
    if (keyPosition == std::string::npos) {
        return ""; // Key not found
    }

    // find a start of the value 
    std::size_t valuePosition = jsonString.find(":", keyPosition);
    if (valuePosition == std::string::npos) {
        return ""; // value not found
    }

    // Find the start of the real value (after the two points)
    valuePosition = jsonString.find_first_not_of(" \t\n\r\f\v", valuePosition + 1);
    if (valuePosition == std::string::npos) {
        return ""; // value not found
    }

    // Find the of the value
    std::size_t endPosition = jsonString.find_first_of(",}", valuePosition);
    if (endPosition == std::string::npos) {
        return ""; // Fim do valor não encontrado
    }

    // extract the value
    std::string value = jsonString.substr(valuePosition, endPosition - valuePosition);

    // remove the qhotation maks if have
    value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());

    return value;
}

int main() {
    // libcurl start the libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a identifier of curl
    CURL* curl = curl_easy_init();
    if (curl) {
        // URL to made a solicitation
        const char* url = "https://jsonplaceholder.typicode.com/todos/1";

        // Configurate a URL for a solicitation
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Configurate a callback function to lead with receive data
        std::string responseData;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // make the request
        CURLcode res = curl_easy_perform(curl);

        // check whether the request was successful
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro na solicitação: %s\n", curl_easy_strerror(res));
        }
        else {
            // show the receive data
            std::cout << "Resposta:\n" << responseData << std::endl;

            // extract especifics values of a JSON
            std::string userId = ExtractJsonValue(responseData, "userId");
            std::string id = ExtractJsonValue(responseData, "id");
            std::string title = ExtractJsonValue(responseData, "title");
            std::string completed = ExtractJsonValue(responseData, "completed");

            // show the extract values
            std::cout << "userId: " << userId << "\n";
            std::cout << "id: " << id << "\n";
            std::cout << "title: " << title << "\n";
            std::cout << "completed: " << completed << "\n";
        }

        // clear and release resources
        curl_easy_cleanup(curl);
    }

    // finish the libcurl
    curl_global_cleanup();

    return 0;
}
//#include <stdio.h>
//#include <string>
//#include <curl/curl.h>

// callback function for the receive data


//int main(void)
//{
//    CURL* curl;
//    CURLcode res;

    /* In windows, this will init the winsock stuff */
//    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */
//    curl = curl_easy_init();
//    if (curl) {
//       /* First set the URL that is about to receive our POST. This URL can
//           just as well be an https:// URL if that is what should receive the
//           data. */
//        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:4000/TokenGenerator/Login");
//        /* Now specify the POST data */
//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "userName=user&password=password");
//
//        /* Perform the request, res will get the return code */
//        res = curl_easy_perform(curl);
//       /* Check for errors */
//        if (res != CURLE_OK)
//            fprintf(stderr, "curl_easy_perform() failed: %s\n",
//               curl_easy_strerror(res));
//
//        /* always cleanup */
//        curl_easy_cleanup(curl);
//    }
//    curl_global_cleanup();
//    return 0;
//}


/*
// Função de callback para lidar com os dados recebidos
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// Função para extrair o valor de uma chave específica em um JSON simples
std::string ExtractTokenFromJson(const std::string& jsonString) {
    // Encontrar a posição da chave "access_token"
    std::size_t tokenPosition = jsonString.find("\"access_token\"");
    if (tokenPosition == std::string::npos) {
        return ""; // Chave "access_token" não encontrada
    }

    // Encontrar o início do valor
    std::size_t valuePosition = jsonString.find(":", tokenPosition);
    if (valuePosition == std::string::npos) {
        return ""; // Valor não encontrado
    }

    // Encontrar o início do valor real (após os dois pontos)
    valuePosition = jsonString.find_first_not_of(" \t\n\r\f\v", valuePosition + 1);
    if (valuePosition == std::string::npos) {
        return ""; // Valor não encontrado
    }

    // Encontrar o fim do valor
    std::size_t endPosition = jsonString.find_first_of(",}", valuePosition);
    if (endPosition == std::string::npos) {
        return ""; // Fim do valor não encontrado
    }

    // Extrair o valor
    std::string token = jsonString.substr(valuePosition, endPosition - valuePosition);

    // Remover aspas se presentes
    token.erase(std::remove(token.begin(), token.end(), '\"'), token.end());

    return token;
}

int main() {
    // Inicializar o libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Criar um identificador de curl
    CURL* curl = curl_easy_init();
    if (curl) {
        // URL para a qual faremos a solicitação
        const char* url = "http://localhost:4000/TokenGenerator/Login";

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "userName=user&password=password");

        // Configurar a URL para a solicitação
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Configurar a função de callback para lidar com os dados recebidos
        std::string responseData;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // Realizar a solicitação
        CURLcode res = curl_easy_perform(curl);

        // Verificar se a solicitação foi bem-sucedida
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro na solicitação: %s\n", curl_easy_strerror(res));
        }
        else {
            // Exibir os dados recebidos
            std::cout << "Resposta:\n" << responseData << std::endl;

            // Extrair o token do JSON
            std::string token = ExtractTokenFromJson(responseData);

            // Exibir o token
            if (!token.empty()) {
                std::cout << "Token: " << token << "\n";
            }
            else {
                std::cerr << "Token não encontrado no JSON.\n";
            }
        }

        // Limpar e liberar recursos
        curl_easy_cleanup(curl);
    }

    // Finalizar o libcurl
    curl_global_cleanup();

    return 0;
}

*/

/*
#include <iostream>
#include <curl/curl.h>
#include <cstring>
#include <map>

// Função de callback para lidar com os dados recebidos
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// Função para extrair valores específicos do JSON
std::map<std::string, std::string> ExtractValuesFromJson(const std::string& jsonString) {
    std::map<std::string, std::string> values;

    // Encontrar a posição da chave "access_token"
    std::size_t tokenPosition = jsonString.find("\"access_token\"");
    if (tokenPosition != std::string::npos) {
        // Encontrar o início do valor
        std::size_t valuePosition = jsonString.find(":", tokenPosition);
        if (valuePosition != std::string::npos) {
            // Encontrar o início do valor real (após os dois pontos)
            valuePosition = jsonString.find_first_not_of(" \t\n\r\f\v", valuePosition + 1);
            if (valuePosition != std::string::npos) {
                // Encontrar o fim do valor
                std::size_t valueEnd = jsonString.find_first_of(",}", valuePosition);
                if (valueEnd != std::string::npos) {
                    // Extrair o valor
                    std::string token = jsonString.substr(valuePosition, valueEnd - valuePosition);
                    // Remover aspas se presentes
                    token.erase(std::remove(token.begin(), token.end(), '\"'), token.end());
                    // Adicionar ao mapa
                    values["access_token"] = token;
                }
            }
        }
    }
    /*
    // Encontrar a posição da chave "user_name"
    std::size_t userNamePosition = jsonString.find("\"user_name\"");
    if (userNamePosition != std::string::npos) {
        // Encontrar o início do valor
        std::size_t valuePosition = jsonString.find(":", userNamePosition);
        if (valuePosition != std::string::npos) {
            // Encontrar o início do valor real (após os dois pontos)
            valuePosition = jsonString.find_first_not_of(" \t\n\r\f\v", valuePosition + 1);
            if (valuePosition != std::string::npos) {
                // Encontrar o fim do valor
                std::size_t valueEnd = jsonString.find_first_of(",}", valuePosition);
                if (valueEnd != std::string::npos) {
                    // Extrair o valor
                    std::string userName = jsonString.substr(valuePosition, valueEnd - valuePosition);
                    // Remover aspas se presentes
                    userName.erase(std::remove(userName.begin(), userName.end(), '\"'), userName.end());
                    // Adicionar ao mapa
                    values["user_name"] = userName;
                }
            }
        }
    }

    // Encontrar a posição da chave "days_to_expire"
    std::size_t daysToExpirePosition = jsonString.find("\"days_to_expire\"");
    if (daysToExpirePosition != std::string::npos) {
        // Encontrar o início do valor
        std::size_t valuePosition = jsonString.find(":", daysToExpirePosition);
        if (valuePosition != std::string::npos) {
            // Encontrar o início do valor real (após os dois pontos)
            valuePosition = jsonString.find_first_not_of(" \t\n\r\f\v", valuePosition + 1);
            if (valuePosition != std::string::npos) {
                // Encontrar o fim do valor
                std::size_t valueEnd = jsonString.find_first_of(",}", valuePosition);
                if (valueEnd != std::string::npos) {
                    // Extrair o valor
                    std::string daysToExpire = jsonString.substr(valuePosition, valueEnd - valuePosition);
                    // Remover aspas se presentes
                    daysToExpire.erase(std::remove(daysToExpire.begin(), daysToExpire.end(), '\"'), daysToExpire.end());
                    // Adicionar ao mapa
                    values["days_to_expire"] = daysToExpire;
                }
            }
        }
    }
    
    return values;
}

class Token {
private:
    std::string token;

public:
    void setValue(const std::string& JsonString) {
        std::map<std::string, std::string> values = ExtractValuesFromJson(JsonString);

        for (const auto& pair : values) {
            token = pair.second;
        }
    }

    std::string getValue() const {
        return token;
    }
};

int main() {
    // Inicializar o libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Criar um identificador de curl
    CURL* curl = curl_easy_init();
    if (curl) {
        // URL para a qual faremos a solicitação
        const char* url = "http://localhost:4000/TokenGenerator/Login";

        // Configurar a URL para a solicitação
        curl_easy_setopt(curl, CURLOPT_URL, url);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "userName=user&password=password");

        // Configurar a função de callback para lidar com os dados recebidos
        std::string responseData;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

        // Realizar a solicitação
        CURLcode res = curl_easy_perform(curl);

        // Verificar se a solicitação foi bem-sucedida
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro na solicitação: %s\n", curl_easy_strerror(res));
        }
        else {
            Token tokenInstance;
            tokenInstance.setValue(responseData);

            std::cout << tokenInstance.getValue() << std::endl;
        }

        // Limpar e liberar recursos
        curl_easy_cleanup(curl);
    }

    // Finalizar o libcurl
    curl_global_cleanup();

    return 0;
}
*/

/*
#include <iostream>
#include <curl/curl.h>
#include <cstring>
#include <map>

class TokenManager {
private:
    CURL* curl;
    std::string responseData;
    std::string accessToken;

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    std::map<std::string, std::string> ExtractValuesFromJson(const std::string& jsonString) {
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

public:
    TokenManager() : curl(curl_easy_init()) {
        if (curl) {
            curl_global_init(CURL_GLOBAL_DEFAULT);
        }
    }

    ~TokenManager() {
        if (curl) {
            curl_easy_cleanup(curl);
            curl_global_cleanup();
        }
    }

    std::string sendRequest(const char* url, const char* payload) {
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

    void requestToken(const char* url, const char* payload) {
        responseData = sendRequest(url, payload);

        std::map<std::string, std::string> values = ExtractValuesFromJson(responseData);

        for (const auto& pair : values) {
            accessToken = pair.second;
        }
    }

    std::string getAccessToken() const {
        return accessToken;
    }
};

int main() {
    TokenManager tokenManager;

    const char* url = "http://localhost:4000/TokenGenerator/Login";
    const char* payload = "userName=user&password=password";

    tokenManager.requestToken(url, payload);

    std::cout << tokenManager.getAccessToken() << std::endl;

    return 0;
}
*/


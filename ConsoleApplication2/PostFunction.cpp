/*
#include <iostream>
#include <curl/curl.h>
#include <cstring>

// Função de callback para lidar com os dados recebidos
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// Função para realizar um pedido POST com dados JSON 
CURLcode PerformPostRequest(const std::string& url, const std::string& jsonData) {
    CURL* curl = curl_easy_init();
    if (curl) {
        // Configurar a URL para a solicitação
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Configurar a solicitação POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Configurar o corpo da solicitação
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        // Configurar a função de callback para lidar com os dados recebidos (se necessário)
        // ...

        // Realizar a solicitação
        CURLcode res = curl_easy_perform(curl);

        // Verificar se a solicitação foi bem-sucedida 
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro na solicitação: %s\n", curl_easy_strerror(res));
        }

        // Limpar e liberar recursos
        curl_easy_cleanup(curl);

        return res;
    }

    return CURLE_FAILED_INIT;
}

int main() {
    // Inicializar o libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // URL para a qual faremos a solicitação POST
    const char* postUrl = "https://...";

    // Dados para o corpo da solicitação POST (valores podem ser ajustados conforme necessário)
    std::string postData = R"({
        "id": 1,
        "name": "example_name",
        "path": "example_path",
        "system_link_path": "example_system_link_path",
        "fk_file_type": 0,
        "fk_file": 0,
        "altitude": 0,
        "latitude": 0,
        "longitude": 0
    })";

    // Realizar o pedido POST
    CURLcode postRes = PerformPostRequest(postUrl, postData);

    // Verificar se o pedido POST foi bem-sucedido
    if (postRes == CURLE_OK) {
        std::cout << "Solicitação POST bem-sucedida.\n";
    }
    else {
        std::cerr << "Erro na solicitação POST.\n";
    }

    // Finalizar o libcurl
    curl_global_cleanup();

    return 0;
}

*/


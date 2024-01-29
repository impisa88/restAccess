/*
#include <iostream>
#include <curl/curl.h>
#include <cstring>

// Fun��o de callback para lidar com os dados recebidos
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// Fun��o para realizar um pedido POST com dados JSON 
CURLcode PerformPostRequest(const std::string& url, const std::string& jsonData) {
    CURL* curl = curl_easy_init();
    if (curl) {
        // Configurar a URL para a solicita��o
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Configurar a solicita��o POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        // Configurar o corpo da solicita��o
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        // Configurar a fun��o de callback para lidar com os dados recebidos (se necess�rio)
        // ...

        // Realizar a solicita��o
        CURLcode res = curl_easy_perform(curl);

        // Verificar se a solicita��o foi bem-sucedida 
        if (res != CURLE_OK) {
            fprintf(stderr, "Erro na solicita��o: %s\n", curl_easy_strerror(res));
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

    // URL para a qual faremos a solicita��o POST
    const char* postUrl = "https://...";

    // Dados para o corpo da solicita��o POST (valores podem ser ajustados conforme necess�rio)
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
        std::cout << "Solicita��o POST bem-sucedida.\n";
    }
    else {
        std::cerr << "Erro na solicita��o POST.\n";
    }

    // Finalizar o libcurl
    curl_global_cleanup();

    return 0;
}

*/


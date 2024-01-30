

#include "token_manager.hh"
#include "post_data.hh"

int main() {
    TokenManager tokenManager;

    const char* urlToken = "http://localhost:4000/TokenGenerator/Login";
    const char* payloadToken = "userName=user&password=password";

    tokenManager.requestToken(urlToken, payloadToken);

    std::string accessToken = tokenManager.getAccessToken();

    std::cout << accessToken << std::endl;

    const char* urlPostData = "http://localhost:4000/files";

    PostData postData(1, "string", "string", "string",
        0, 0, 0, 0, 0);

    std::string response = postData.sendPostData(urlPostData, accessToken);

    std::cout << "Response from POST request:\n" << response << std::endl;

    return 0;
}


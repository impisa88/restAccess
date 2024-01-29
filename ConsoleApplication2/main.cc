/*

#include "token_manager.hh"
#include "post_data.hh"

int main() {
    TokenManager tokenManager;

    const char* url = "http://localhost:4000/TokenGenerator/Login";
    const char* payload = "userName=user&password=password";

    tokenManager.requestToken(url, payload);

    std::cout << tokenManager.getAccessToken() << std::endl;

    PostData postData(1, "example_name", "example_path", "example_system_link_path",
        0, 0, 0, 0, 0);

    std::string postJson = postData.toJsonString();

    std::cout << " " << std::endl;
    std::cout << postJson << std::endl;


    return 0;
}

*/


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

    /*PostData postData(1, "example_name", "example_path", "example_system_link_path",
        0, 0, 0, 0, 0);*/

    PostData postData("test", "path", "systemPath", 1, 1, 1.0, 1.0);

    std::string response = postData.sendPostData(urlPostData, accessToken);

    std::cout << "Response from POST request:\n" << response << std::endl;

    return 0;
}


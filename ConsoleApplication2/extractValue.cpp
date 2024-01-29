#include <iostream>


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
        return ""; // end of the value not found
    }

    // extract the value
    std::string value = jsonString.substr(valuePosition, endPosition - valuePosition);

    // remove the qhotation maks if have
    value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());

    return value;
}
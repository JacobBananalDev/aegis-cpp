#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

/*
    Converts Base64URL string to standard Base64 format.
*/
std::string Base64UrlToBase64(std::string input)
{
    std::replace(input.begin(), input.end(), '-', '+');
    std::replace(input.begin(), input.end(), '_', '/');

    // Add padding if missing
    while (input.size() % 4 != 0)
    {
        input += '=';
    }

    return input;
}

/*
    Basic Base64 decoding implementation.
*/
std::string Base64Decode(const std::string& input)
{
    static const std::string chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    std::string output;
    std::vector<int> T(256, -1);

    for (int i = 0; i < 64; i++)
        T[chars[i]] = i;

    int val = 0, valb = -8;

    for (unsigned char c : input)
    {
        if (T[c] == -1) break;

        val = (val << 6) + T[c];
        valb += 6;

        if (valb >= 0)
        {
            output.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }

    return output;
}

/*
 
    splits a string by a given delimiter

    Used here to seperate JWT into: 
    header.paylod.signature
 
*/
std::vector<std::string> Split(const std::string& str, char delimiter)
{
    std::vector<std::string> parts;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter))
    {
        parts.push_back(item);
    }

    return parts;
}

/*
    Entry point for Aegis security engine.

    Expected usage:
        aegis <jwt_token>

    Example:
        aegis abc.def.ghi
*/
int main(int argc, char* argv[])
{
    // Validate that a token argument was provided
    if (argc < 2)
    {
        std::cout << "Usage: aegis <jwt_token>\n";
        return 1;
    }

    std::string token = argv[1];

    // Split the token into its components
    auto parts = Split(token, '.');

    // A valid JWT must have exactly 3 parts
    if (parts.size() != 3)
    {
        std::cerr << "Invalid JWT format. Expected 3 parts.\n";
        return 1;
    }

    // Decode header and payload
    std::string header = Base64Decode(Base64UrlToBase64(parts[0]));
    std::string payload = Base64Decode(Base64UrlToBase64(parts[1]));

    // If structure is valid, print components
    std::cout << "JWT structure valid.\n";
    std::cout << "Decoded Header:\n" << header << "\n\n";
    std::cout << "Decoded Payload:\n" << payload << "\n";
    std::cout << "Signature: " << parts[2] << "\n";

    return 0;
}

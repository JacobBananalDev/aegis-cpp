#include <iostream>
#include "jwt/JwtUtils.h"

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

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

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

    // If structure is valid, print components
    std::cout << "JWT structure valid.\n";
    std::cout << "Header: " << parts[0] << "\n";
    std::cout << "Payload: " << parts[1] << "\n";
    std::cout << "Signature: " << parts[2] << "\n";

    return 0;
}

#include "JwtUtils.h"
#include <sstream>
#include <algorithm>

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
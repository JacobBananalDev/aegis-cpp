#include "JwtUtils.h"
#include <sstream>
#include <algorithm>

#include "../external/json.hpp"
using json = nlohmann::json;

#include <chrono>
#include <iostream>

bool ValidateClaims(const std::string& payload, const std::string& expectedIssuer)
{
    try
    {
        json j = json::parse(payload);

        // Validate issuer
        if (!j.contains("iss") || j["iss"] != expectedIssuer)
        {
            std::cerr << "Issuer validation failed.\n";
            return false;
        }

        // Validate expiration
        if (!j.contains("exp"))
        {
            std::cerr << "Expiration claim missing.\n";
            return false;
        }

        long long exp = j["exp"];

        auto now = std::chrono::system_clock::now();
        auto nowSeconds = std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()).count();

        if (exp < nowSeconds)
        {
            std::cerr << "Token expired.\n";
            return false;
        }

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Invalid JSON payload: " << e.what() << "\n";
        return false;
    }
}


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
#pragma once
#include <string>
#include <vector>

std::vector<std::string> Split(const std::string& str, char delimiter);
std::string Base64UrlToBase64(std::string input);
std::string Base64Decode(const std::string& input);
bool ValidateClaims(const std::string& payload, const std::string& expectedIssuer);

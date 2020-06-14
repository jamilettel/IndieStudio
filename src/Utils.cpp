/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Utils
*/

#include "Utils.hpp"
#include <fstream>

using namespace is;

bool Utils::loadFileInArray(const std::string &filepath, std::vector<std::string> &lines)
{
    std::ifstream saveFile;
    std::string line;

    saveFile.open(filepath, std::ios_base::in);
    if (!saveFile.is_open())
        return false;
    while (std::getline(saveFile, line)) {
        lines.emplace_back(line);
    }
    return true;
}

std::vector<std::string> Utils::strtok(std::string str, const std::string &sep)
{
    std::vector<std::string> array;
    size_t pos = 0;
    std::string token;

    if (str.empty())
        return array;

    while ((pos = str.find(sep)) != std::string::npos) {
        token = str.substr(0, pos);
        array.emplace_back(token);
        str.erase(0, pos + sep.length());
    }
    array.emplace_back(str);
    return array;
}

bool Utils::isValidNum(const std::string &string)
{
    size_t i = 0;
    bool dot = false;
    bool num = false;

    if (!string.size() || (string.size() == 1 && string[0] == '-'))
        return false;
    if (string[0] == '-')
        i++;
    for (; i < string.size(); i++) {
        if (string[i] == '.' && num && !dot) {
            dot = true;
            num = false;
            continue;
        }
        if (string[i] < '0' || string[i] > '9')
            return false;
        num = true;
    }
    return num;
}

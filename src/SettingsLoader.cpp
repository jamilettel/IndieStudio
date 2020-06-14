/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** SettingsLoader
*/

#include "SettingsLoader.hpp"
#include "Utils.hpp"
#include <fstream>

using namespace is;

void SettingsLoader::write(const std::string &filepath)
{
    std::ofstream saveFile;

    saveFile.open(filepath, std::ios_base::out | std::ios_base::trunc);
    if (!saveFile.is_open())
        return;
    for (auto &pair : _values) {
        saveFile << pair.first << "=" << pair.second << std::endl;
    }
}

bool SettingsLoader::loadFile(const std::string &filepath)
{
    std::vector<std::string> lines;

    if (!Utils::loadFileInArray(filepath, lines))
        return false;
    for (auto &line: lines) {
        auto parts = Utils::strtok(line, "=");

        if (parts.size() == 2) {
            _values[parts[0]] = parts[1];
        }
    }
    return true;
}

bool SettingsLoader::getValue(const std::string &key, std::string &value) const
{
    if (!_values.count(key))
        return false;
    value = _values.at(key);
    return true;
}

void SettingsLoader::setValue(const std::string &key, const std::string &value)
{
    _values[key] = value;
}

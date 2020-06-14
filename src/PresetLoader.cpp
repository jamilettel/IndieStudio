/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** PresetLoader
*/

#include "PresetLoader.hpp"
#include <fstream>
#include <algorithm>

using namespace is;

PresetLoader::PresetLoader()
{
    _keyboardBindings.reserve(4);
    _joystickBindings.reserve(4);
    for (int i = 0; i < 4; i++) {
        _keyboardBindings.emplace_back();
        _joystickBindings.emplace_back();
    }
}

bool PresetLoader::loadFileInArray(const std::string &filepath, std::vector<std::string> &lines)
{
    std::ifstream saveFile;
    std::string line;

    saveFile.open(filepath, std::ios_base::in);
    if (!saveFile.is_open())
        return false;
    lines.reserve(4 * LINE_PER_PRESET);
    while (std::getline(saveFile, line)) {
        lines.emplace_back(line);
    }
    return true;
}

bool PresetLoader::checkFileContents(std::vector<std::string> &lines)
{
    return true;
}

bool PresetLoader::loadFile(const std::string &filepath)
{
    std::vector<std::string> lines;

    if (!loadFileInArray(filepath, lines) || !checkFileContents(lines))
        return false;
    return true;

}

void PresetLoader::loadPreset(is::components::PresetComponent &preset)
{
}

void PresetLoader::savePreset(is::components::PresetComponent &preset)
{
    int pos = preset.presetNumber - 1;

    _joystickBindings[pos] = preset.getJoystickPreset().getBindings();
    _keyboardBindings[pos] = preset.getKeyboardPreset().getBindings();
}

void PresetLoader::write(const std::string &filepath)
{
    std::ofstream saveFile;

    saveFile.open(filepath, std::ios_base::out | std::ios_base::trunc);
    if (!saveFile.is_open())
        return;
    for (int i = 0; i < 4; i++) {
        for (auto &pair : _joystickBindings[i])
            saveFile << "J" << i + 1 << ":" << pair.first.action << ":" << pair.first.description
                     << ":" << pair.first.value << ":" << pair.first.max << ":" << pair.second << std::endl;
        for (auto &pair : _keyboardBindings[i]) {
            saveFile << "K" << i + 1 << ":" << pair.first.action << ":" << pair.first.description
                     << ":" << pair.first.value << ":" << pair.first.max << ":" << static_cast<int>(pair.second) << std::endl;
        }
    }
}

std::vector<std::string> PresetLoader::strtok(std::string str, const std::string &sep)
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
    return array;
}

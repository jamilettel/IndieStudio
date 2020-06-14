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

bool PresetLoader::isValidNum(const std::string &string)
{
    size_t i = 0;

    if (!string.size() || (string.size() == 1 && string[0] == '-'))
        return false;
    if (string[0] == '-')
        i++;
    for (; i < string.size(); i++) {
        if (string[i] < '0' || string[i] > '9')
            return false;
    }
    return true;
}

bool PresetLoader::checkLine(std::vector<std::string> &line)
{
    if (line.size() != 6)
        return false;
    if (line[0].size() != 2)
        return false;
    if (line[0][0] != 'J' && line[0][0] != 'K')
        return false;
    if (line[0][1] < '1' || line[0][1] > '4')
        return false;
    if (!line[1].size() || !line[2].size())
        return false;
    if (!isValidNum(line[3]) || !isValidNum(line[5]))
        return false;
    if (line[4].size() != 1 || (line[4][0] != '0' && line[4][0] != '1'))
        return false;
    return true;
}

void PresetLoader::fillPreset(bool kbd, int presetNb, const PresetAction &action, int key)
{
    if (kbd) {
        _keyboardBindings[presetNb - 1][action] = static_cast<irr::EKEY_CODE>(key);
    } else {
        _joystickBindings[presetNb - 1][action] = key;
    }
}

bool PresetLoader::loadFile(const std::string &filepath)
{
    std::vector<std::string> lines;

    if (!loadFileInArray(filepath, lines))
        return false;
    for (auto &line: lines) {
        PresetAction action;
        auto parts = strtok(line, ":");
        if (!checkLine(parts))
            return false;

        bool keyboard = parts[0][0] == 'K';
        int presetNb = parts[0][1] - '0';
        int key = std::stoi(parts[5]);

        action.action = parts[1];
        action.description = parts[2];
        action.value = std::stof(parts[3]);
        action.max = static_cast<bool>(std::stoi(parts[4]));
        fillPreset(keyboard, presetNb, action, key);
    }
    return true;

}

void PresetLoader::loadPreset(is::components::PresetComponent &preset)
{
    int pos = preset.presetNumber - 1;

    for (auto &pair : _joystickBindings[pos]) {
        preset.getJoystickPreset().bind(pair.second, pair.first);
    }
    for (auto &pair : _keyboardBindings[pos]) {
        preset.getKeyboardPreset().bind(pair.second, pair.first);
    }
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
    array.emplace_back(str);
    return array;
}

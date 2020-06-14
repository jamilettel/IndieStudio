/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** PresetLoader
*/

#ifndef PRESETLOADER_HPP_
#define PRESETLOADER_HPP_

#include <string>
#include "Components/Preset.hpp"

#define LINE_PER_KEYBOARD_PRESET 5
#define LINE_PER_JOYSTICK_PRESET 8
#define LINE_PER_PRESET LINE_PER_JOYSTICK_PRESET + LINE_PER_KEYBOARD_PRESET

namespace is {

    class PresetLoader {
    public:
        PresetLoader();
        ~PresetLoader() = default;

        PresetLoader(const PresetLoader &) = default;
        PresetLoader &operator=(const PresetLoader &) = default;

        /// Opens, reads, checks if the file is valid and stores it in this class.
        bool loadFile(const std::string &filepath);

        /// Used after open, fills the preset with what was written in the file.
        void loadPreset(is::components::PresetComponent &preset);

        /// Saves the preset in memory, will be written with write().
        void savePreset(is::components::PresetComponent &preset);

        /// Use after saving the presets to write the file to the system.
        void write(const std::string &filepath);

    private:
        bool loadFileInArray(const std::string &filePath, std::vector<std::string> &lines);
        bool checkFileContents(std::vector<std::string> &lines);
        static std::vector<std::string> strtok(std::string str, const std::string& sep);

    private:
        std::vector<std::map<PresetAction, irr::EKEY_CODE>> _keyboardBindings;
        std::vector<std::map<PresetAction, irr::s32>> _joystickBindings;

    };

}

#endif /* !PRESETLOADER_HPP_ */

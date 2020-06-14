/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** PresetLoader
*/

#ifndef SETTINGSLOADER_HPP_
#define SETTINGSLOADER_HPP_

#include <map>
#include <string>
#include "Components/Preset.hpp"

#ifndef RESOURCES_PATH
    #define RESOURCES_PATH "./resources/"
#endif

#define SETTINGS_SAVE_FILE RESOURCES_PATH ".saveSettings"

namespace is {

    class SettingsLoader {
    public:
        SettingsLoader() = default;
        ~SettingsLoader() = default;

        SettingsLoader(const SettingsLoader &) = default;
        SettingsLoader &operator=(const SettingsLoader &) = default;

        /// Opens, reads, checks if the file is valid and stores information in this class.
        bool loadFile(const std::string &filepath = SETTINGS_SAVE_FILE);

        /// Use after setting values to write the file to the system.
        void write(const std::string &filepath = SETTINGS_SAVE_FILE);

        bool getValue(const std::string &key, std::string &value) const;

        void setValue(const std::string &key, const std::string &value);

    private:
        std::map<std::string, std::string> _values;

    };

}

#endif /* !SETTINGSLOADER_HPP_ */

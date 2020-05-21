/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** PresetAction
*/

#ifndef PRESETACTION_HPP_
#define PRESETACTION_HPP_

#include <string>

namespace is {

    struct PresetAction {
        PresetAction() = delete;
        PresetAction(std::string actionString, float target, std::string desc);

        PresetAction(const PresetAction &action) = default;
        ~PresetAction() = default;

        PresetAction &operator=(const PresetAction &action) = default;
        bool operator==(const PresetAction &rhs) const;

        bool operator<(const PresetAction &rhs) const;
        bool operator>(const PresetAction &rhs) const;

        std::string action;
        float value = 0;
        std::string description;

    };

}

#endif /* !PRESETACTION_HPP_ */

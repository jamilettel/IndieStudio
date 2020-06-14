/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** PresetAction
*/

#ifndef PRESETACTION_HPP_
#define PRESETACTION_HPP_

#include <string>
#include <utility>

namespace is {

    struct PresetAction {
        PresetAction() = default;
        PresetAction(
            std::string actionString,
            float target,
            std::string desc,
            bool maximum = false
            );
        PresetAction(const PresetAction &action) = default;
        ~PresetAction() = default;

        PresetAction &operator=(const PresetAction &action) = default;
        bool operator==(const PresetAction &rhs) const;

        bool operator<(const PresetAction &rhs) const;
        bool operator>(const PresetAction &rhs) const;

        std::string action;
        float value = 0;
        std::string description;
        // only used for joystick axes
        bool max = false;

    };

}

#endif /* !PRESETACTION_HPP_ */

/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Character
*/

#ifndef CHARACTERCOMPONENT_HPP_
#define CHARACTERCOMPONENT_HPP_

#include "ECS/Component.hpp"

namespace is::components {

    class CharacterComponent: is::ecs::Component {
    public:
        enum Type {
            AI,
            KEYBOARD_PLAYER,
            JOYSTICK_PLAYER
        };
    public:
        CharacterComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            int characterNumber
            );
        ~CharacterComponent() = default;

        CharacterComponent(const CharacterComponent &) = delete;
        CharacterComponent &operator=(const CharacterComponent &) = delete;

        int number;

        Type characterType = AI;

        int joystickId = -1;
        int presetNumber = -1;

    private:
    };

}

#endif /* !CHARACTERCOMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Keyboard Input
*/

#ifndef KEYBOARDINPUTCOMPONENT_HPP_
#define KEYBOARDINPUTCOMPONENT_HPP_

#include <string>

#include "Components/InputManager.hpp"
#include "EventManager/EventManager.hpp"

namespace is::components {

    class KeyboardInputComponent: public is::ecs::Component {
    public:
        KeyboardInputComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            InputManagerComponent &inputManager
            );
        ~KeyboardInputComponent() override = default;

        KeyboardInputComponent(const KeyboardInputComponent &) = delete;
        KeyboardInputComponent &operator=(const KeyboardInputComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] bool isBound(EKEY_CODE key) const;

        void bind(EKEY_CODE key, const std::string &action, float target);
        void unbind(EKEY_CODE key);
        bool changeKey(EKEY_CODE from, EKEY_CODE to);
        bool changeTarget(EKEY_CODE key, float target);

        std::map<EKEY_CODE, std::pair<std::string, float>> &getBindings();
        [[nodiscard]] InputManagerComponent &getInputManager() const;

        void unbindAll();

    private:
        InputManagerComponent &_inputManager;
        std::map<EKEY_CODE, std::pair<std::string, float>> _bindings;
    };

}

#endif /* !KEYBOARDINPUTCOMPONENT_HPP_ */

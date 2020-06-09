/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Keyboard Input
*/

#ifndef KEYBOARDINPUTCOMPONENT_HPP_
#define KEYBOARDINPUTCOMPONENT_HPP_

#include "Components/InputManager.hpp"
#include "Components/KeyboardPreset.hpp"

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

        [[nodiscard]] bool isBound(irr::EKEY_CODE key) const;

        void bind(irr::EKEY_CODE key, const std::string &action, float target);
        void unbind(irr::EKEY_CODE key);
        bool changeKey(irr::EKEY_CODE from, irr::EKEY_CODE to);
        bool changeTarget(irr::EKEY_CODE key, float target);

        void setPreset(const KeyboardPresetComponent &preset);

        const std::map<irr::EKEY_CODE, std::pair<std::string, float>> &getBindings() const;
        [[nodiscard]] InputManagerComponent &getInputManager() const;

        void unbindAll();

    private:
        InputManagerComponent &_inputManager;
        std::map<irr::EKEY_CODE, std::pair<std::string, float>> _bindings;
    };

}

#endif /* !KEYBOARDINPUTCOMPONENT_HPP_ */

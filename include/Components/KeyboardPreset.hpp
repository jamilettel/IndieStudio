/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** KeyboardPreset
*/

#ifndef KEYBOARDPRESETCOMPONENT_HPP_
#define KEYBOARDPRESETCOMPONENT_HPP_

#include "ECS/Component.hpp"
#include <string>
#include "EventManager/EventManager.hpp"
#include "PresetAction.hpp"

namespace is::components {

    class KeyboardPresetComponent: public is::ecs::Component {
    public:

        KeyboardPresetComponent(
            std::shared_ptr<is::ecs::Entity> &e
            );
        ~KeyboardPresetComponent() = default;

        KeyboardPresetComponent(const KeyboardPresetComponent &) = delete;
        KeyboardPresetComponent &operator=(const KeyboardPresetComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] bool isBound(EKEY_CODE key) const;

        void bind(EKEY_CODE key, const PresetAction &action);
        bool changeKey(EKEY_CODE from, EKEY_CODE to);

        const std::map<PresetAction, EKEY_CODE> &getBindings() const;

    private:
        std::map<PresetAction, EKEY_CODE> _bindings;
    };

}

#endif /* !KEYBOARDPRESETCOMPONENT_HPP_ */

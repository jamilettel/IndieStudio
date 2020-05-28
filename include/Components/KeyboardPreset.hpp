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
#include <algorithm>

namespace is::components {

    class KeyboardPresetComponent: public is::ecs::Component {
    public:

        explicit KeyboardPresetComponent(
            std::shared_ptr<is::ecs::Entity> &e
            );
        ~KeyboardPresetComponent() override = default;

        KeyboardPresetComponent(const KeyboardPresetComponent &) = delete;
        KeyboardPresetComponent &operator=(const KeyboardPresetComponent &) = delete;

        void deleteComponent() override;
        [[nodiscard]] bool isBound(EKEY_CODE key) const;

        void bind(EKEY_CODE key, const PresetAction &action);
        bool changeKey(EKEY_CODE from, EKEY_CODE to);

        [[nodiscard]] const std::map<PresetAction, EKEY_CODE> &getBindings() const;

        static void createBasicPreset(KeyboardPresetComponent &preset);

    private:
        std::map<PresetAction, EKEY_CODE> _bindings;
    };

}

#endif /* !KEYBOARDPRESETCOMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** KeyboardPreset
*/

#ifndef KEYBOARDPRESETCOMPONENT_HPP_
#define KEYBOARDPRESETCOMPONENT_HPP_

#include <irrlicht.h>
#include <functional>
#include <map>
#include <algorithm>

#include "ECS/Component.hpp"
#include "PresetAction.hpp"

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
        [[nodiscard]] bool isBound(irr::EKEY_CODE key) const;

        void bind(irr::EKEY_CODE key, const PresetAction &action);
        bool changeKey(irr::EKEY_CODE from, irr::EKEY_CODE to);

        [[nodiscard]] const std::map<PresetAction, irr::EKEY_CODE> &getBindings() const;

        static void createBasicPreset(KeyboardPresetComponent &preset);

    private:
        std::map<PresetAction, irr::EKEY_CODE> _bindings;
    };

}

#endif /* !KEYBOARDPRESETCOMPONENT_HPP_ */

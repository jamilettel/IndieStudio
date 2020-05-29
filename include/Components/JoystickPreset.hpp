/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickPreset
*/

#ifndef JOYSTICKPRESETCOMPONENT_HPP_
#define JOYSTICKPRESETCOMPONENT_HPP_

#include "ECS/Component.hpp"
#include <string>
#include "EventManager/EventManager.hpp"
#include "PresetAction.hpp"
#include <algorithm>

namespace is::components {

    class JoystickPresetComponent: public is::ecs::Component {
    public:
        explicit JoystickPresetComponent(
            std::shared_ptr<is::ecs::Entity> &e
            );
        ~JoystickPresetComponent() override = default;

        JoystickPresetComponent(const JoystickPresetComponent &) = delete;
        JoystickPresetComponent &operator=(const JoystickPresetComponent &) = delete;

        void deleteComponent() override;

        // [[nodiscard]] bool isButtonBound(u32 button) const;

        // void unbindButton(u32 button);
        // void bindButton(u32 button, const PresetAction &action);
        // bool changeButton(u32 from, u32 to);

        // [[nodiscard]] bool isAxisBound(u32 button) const;

        // void unbindAxis(u32 axis);
        // void bindAxis(u32 axis, const PresetAction &action);
        // bool changeAxis(u32 from, u32 to);

        // [[nodiscard]] const std::map<PresetAction, u32> &getButtonBindings() const;
        // [[nodiscard]] const std::map<PresetAction, u32> &getAxisBindings() const;

        [[nodiscard]] bool isBound(s32 binding) const;

        // void unbind(u32 button);
        void bind(s32 binding, const PresetAction &action);
        bool changeBinding(s32 from, s32 to);


        [[nodiscard]] const std::map<PresetAction, s32> &getBindings() const;

        static void createBasicPreset(JoystickPresetComponent &preset);

    private:
        // std::map<PresetAction, u32> _buttons;
        // std::map<PresetAction, u32> _axes;
        std::map<PresetAction, s32> _bindings;

    };

}

#endif /* !JOYSTICKPRESETCOMPONENT_HPP_ */

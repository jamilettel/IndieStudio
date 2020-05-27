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
        JoystickPresetComponent(
            std::shared_ptr<is::ecs::Entity> &e
            );
        ~JoystickPresetComponent() = default;

        JoystickPresetComponent(const JoystickPresetComponent &) = delete;
        JoystickPresetComponent &operator=(const JoystickPresetComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] bool isButtonBound(u32 button) const;

        void bindButton(u32 button, const PresetAction &action);
        bool changeButton(u32 from, u32 to);

        [[nodiscard]] bool isAxisBound(u32 button) const;

        void bindAxis(u32 button, const PresetAction &action);
        bool changeAxis(u32 from, u32 to);

        const std::map<PresetAction, u32> &getButtonBindings() const;
        const std::map<PresetAction, u32> &getAxisBindings() const;
        [[nodiscard]] std::map<PresetAction, u32> getBindings() const;

        static void createBasicPreset(JoystickPresetComponent &preset);

    private:
        std::map<PresetAction, u32> _buttons;
        std::map<PresetAction, u32> _axes;

    };

}

#endif /* !JOYSTICKPRESETCOMPONENT_HPP_ */

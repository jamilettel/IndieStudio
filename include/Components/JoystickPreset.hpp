/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickPreset
*/

#ifndef JOYSTICKPRESETCOMPONENT_HPP_
#define JOYSTICKPRESETCOMPONENT_HPP_

#include <irrlicht.h>
#include <algorithm>

#include <map>

#include "ECS/Component.hpp"
#include "PresetAction.hpp"

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

        [[nodiscard]] bool isBound(irr::s32 binding) const;

        void bind(irr::s32 binding, const PresetAction &action);
        bool changeBinding(irr::s32 from, irr::s32 to);

        void bindAxis(irr::s32 binding, const PresetAction &action);

        [[nodiscard]] const std::map<PresetAction, irr::s32> &getBindings() const;

        static void createBasicPreset(JoystickPresetComponent &preset);

    private:
        std::map<PresetAction, irr::s32> _bindings;

    };

}

#endif /* !JOYSTICKPRESETCOMPONENT_HPP_ */

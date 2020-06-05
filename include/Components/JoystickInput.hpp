/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickInput
*/

#ifndef JOYSTICKINPUTCOMPONENT_HPP_
#define JOYSTICKINPUTCOMPONENT_HPP_

#include "Components/InputManager.hpp"
#include "Components/JoystickPreset.hpp"

#define JOYSTICK_MAX_AXIS_VALUE 32768.0

namespace is::components {

    class JoystickInputComponent: public is::ecs::Component {
    public:
        JoystickInputComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            InputManagerComponent &inputManager
            );
        ~JoystickInputComponent() override = default;

        JoystickInputComponent(const JoystickInputComponent &) = delete;
        JoystickInputComponent &operator=(const JoystickInputComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] bool isButtonBound(irr::u32 button) const;
        void bindButton(irr::u32 button, const std::string &action, float target);
        void unbindButton(irr::u32 button);
        bool changeButton(irr::u32 from, irr::u32 to);
        bool changeButtonTarget(irr::u32 button, float target);

        [[nodiscard]] bool isAxisBound(irr::u32 axis) const;
        void bindAxis(irr::u32 axis, const std::string &action, float min, float max);
        void unbindAxis(irr::u32 axis);
        bool changeAxis(irr::u32 from, irr::u32 to);
        bool changeAxisTargets(irr::u32 axis, float min, float max);
        bool changeAxisTarget(irr::u32 axis, float newTarget, bool max);

        std::map<irr::u32, std::pair<std::string, float>> &getButtonBindings();
        std::map<irr::u32, std::pair<std::string, float[2]>> &getAxisBindings();
        [[nodiscard]] InputManagerComponent &getInputManager() const;

        void assignJoystick(int id);
        [[nodiscard]] int getJoystickId() const;

        void unbindAll();

        void setPreset(const JoystickPresetComponent &preset);

        double axisDeadzoneMin = 0.20;
        double axisDeadzoneMax = 0.90;

    private:
        InputManagerComponent &_inputManager;
        std::map<irr::u32, std::pair<std::string, float>> _buttons;
        std::map<irr::u32, std::pair<std::string, float[2]>> _axes;
        int _joystickId = -1;
    };

}

#endif /* !JOYSTICKINPUTCOMPONENT_HPP_ */

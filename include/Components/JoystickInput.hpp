/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickInput
*/

#ifndef JOYSTICKINPUTCOMPONENT_HPP_
#define JOYSTICKINPUTCOMPONENT_HPP_

#include "Components/InputManager.hpp"
#include "EventManager/EventManager.hpp"
#include <string>

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

            [[nodiscard]] bool isButtonBound(u32 button) const;
            void bindButton(u32 button, const std::string &action, float target);
            void unbindButton(u32 button);
            bool changeButton(u32 from, u32 to);
            bool changeButtonTarget(u32 button, float target);

            [[nodiscard]] bool isAxisBound(u32 axis) const;
            void bindAxis(u32 axis, const std::string &action, float min, float max);
            void unbindAxis(u32 axis);
            bool changeAxis(u32 from, u32 to);
            bool changeAxisTarget(u32 axis, float min, float max);

            std::map<u32, std::pair<std::string, float>> &getButtonBindings();
            std::map<u32, std::pair<std::string, float[2]>> &getAxisBindings();
            [[nodiscard]] InputManagerComponent &getInputManager() const;

            void assignJoystick(int id);
            [[nodiscard]] int getJoystickId() const;

            void unbindAll();

            float axisDeadzoneMin = 0.15;
            float axisDeadzoneMax = 0.85;

        private:
            InputManagerComponent &_inputManager;
            std::map<u32, std::pair<std::string, float>> _buttons;
            std::map<u32, std::pair<std::string, float[2]>> _axes;
            int _joystickId = -1;
    };

}

#endif /* !JOYSTICKINPUTCOMPONENT_HPP_ */

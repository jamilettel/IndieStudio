/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickCursor
*/

#ifndef JOYSTICKCURSORCOMPONENT_HPP_
#define JOYSTICKCURSORCOMPONENT_HPP_

#include "Components/Cursor.hpp"
#include "Components/JoystickInput.hpp"

namespace is::components {

    class JoystickCursorComponent: public is::ecs::Component {
    public:
        JoystickCursorComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            CursorComponent &cursor,
            JoystickInputComponent &joystickInput
            );
        ~JoystickCursorComponent() override = default;

        JoystickCursorComponent(const JoystickCursorComponent &) = delete;
        JoystickCursorComponent &operator=(const JoystickCursorComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] int getJoystickId() const;
        [[nodiscard]] JoystickInputComponent &getJoystickInput() const;
        [[nodiscard]] WindowComponent &getWindow() const;
        [[nodiscard]] CursorComponent &getCursor() const;

        bool clicked = false;

    private:
        JoystickInputComponent &_joystickInput;
        CursorComponent &_cursor;
    };

}

#endif /* !JOYSTICKCURSORCOMPONENT_HPP_ */

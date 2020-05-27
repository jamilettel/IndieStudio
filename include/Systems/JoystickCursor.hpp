/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** JoystickCursor
*/

#ifndef JOYSTICKCURSORSYSTEM_HPP_
#define JOYSTICKCURSORSYSTEM_HPP_

#include "ECS/ASystem.hpp"

namespace is::systems {

    class JoystickCursorSystem: public is::ecs::ASystem {
    public:
        JoystickCursorSystem() = default;
        ~JoystickCursorSystem() = default;

        JoystickCursorSystem(const JoystickCursorSystem &) = default;
        JoystickCursorSystem &operator=(const JoystickCursorSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

    protected:
    private:
    };

}

#endif /* !JOYSTICKCURSORSYSTEM_HPP_ */

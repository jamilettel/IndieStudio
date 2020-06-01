/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Cursor
*/

#ifndef CUSRORSYSTEM_HPP_
#define CUSRORSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/Cursor.hpp"

namespace is::systems {

    class CursorSystem: public is::ecs::ASystem {
    public:
        CursorSystem() = default;
        ~CursorSystem() override = default;

        CursorSystem(const CursorSystem &) = default;
        CursorSystem &operator=(const CursorSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

    };

}

#endif /* !CUSRORSYSTEM_HPP_ */

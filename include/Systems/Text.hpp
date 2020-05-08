/*
** EPITECH PROJECT, 2020
** include/Systems/TextSystem.hpp
** File description:
** 
*/

#ifndef TEXTSYSTEM_HPP
#   define TEXTSYSTEM_HPP

#   include "ECS/ASystem.hpp"

#   include "Components/Text.hpp"
#   include "Exception.hpp"

namespace is::systems {

    class TextSystem: public is::ecs::ASystem {
        public:
            TextSystem() = default;
            ~TextSystem() = default;

            TextSystem(const TextSystem &) = default;
            TextSystem &operator=(const TextSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}

#endif

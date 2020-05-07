/*
** EPITECH PROJECT, 2020
** include/Systems/SystemAudio.hpp
** File description:
** 
*/

#ifndef AUDIOSYSTEM_HPP
#   define AUDIOSYSTEM_HPP

#   include "ECS/ASystem.hpp"

#   include "Components/Audio.hpp"

namespace is::systems {

    class SystemAudio: public is::ecs::ASystem {
        public:
            SystemAudio() = default;
            ~SystemAudio() = default;

            SystemAudio(const SystemAudio &) = default;
            SystemAudio &operator=(const SystemAudio &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}

#endif

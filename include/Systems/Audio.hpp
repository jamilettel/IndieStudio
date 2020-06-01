/*
** EPITECH PROJECT, 2020
** include/Systems/AudioSystem.hpp
** File description:
** 
*/

#ifndef AUDIOSYSTEM_HPP
#define AUDIOSYSTEM_HPP

#include "ECS/ASystem.hpp"

#include "Components/Audio.hpp"

namespace is::systems {

    class AudioSystem: public is::ecs::ASystem {
        public:
            AudioSystem() = default;
            ~AudioSystem() override = default;

            AudioSystem(const AudioSystem &) = default;
            AudioSystem &operator=(const AudioSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}

#endif

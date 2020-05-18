/*
** EPITECH PROJECT, 2020
** include/Systems/ParticuleSystem.hpp
** File description:
** 
*/

#ifndef PARTICULESYSTEM_HPP
#   define PARTICULESYSTEM_HPP

#   include "ECS/ASystem.hpp"

#   include "Components/Particule.hpp"
#   include "Exception.hpp"

namespace is::systems {

    class ParticuleSystem: public is::ecs::ASystem {
        public:
            ParticuleSystem() = default;
            ~ParticuleSystem() override = default;

            ParticuleSystem(const ParticuleSystem &) = default;
            ParticuleSystem &operator=(const ParticuleSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}

#endif

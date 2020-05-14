/*
** EPITECH PROJECT, 2020
** include/Systems/SliderSystem.hpp
** File description:
** 
*/

#ifndef SLIDERSYSTEM_HPP
#   define SLIDERSYSTEM_HPP

#   include "ECS/ASystem.hpp"

#   include "Components/Slider.hpp"
#   include "Exception.hpp"

namespace is::systems {

    class SliderSystem: public is::ecs::ASystem {
        public:
            SliderSystem() = default;
            ~SliderSystem() override = default;

            SliderSystem(const SliderSystem &) = default;
            SliderSystem &operator=(const SliderSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}

#endif

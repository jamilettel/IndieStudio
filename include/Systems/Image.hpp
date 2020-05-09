/*
** EPITECH PROJECT, 2020
** include/Systems/ImageSystem.hpp
** File description:
** 
*/

#ifndef IMAGESYSTEM_HPP
#   define IMAGESYSTEM_HPP

#   include "ECS/ASystem.hpp"

#   include "Components/Image.hpp"
#   include "Exception.hpp"

namespace is::systems {

    class ImageSystem: public is::ecs::ASystem {
        public:
            ImageSystem() = default;
            ~ImageSystem() = default;

            ImageSystem(const ImageSystem &) = default;
            ImageSystem &operator=(const ImageSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}

#endif

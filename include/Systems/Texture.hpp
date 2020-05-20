/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Texture
*/

#ifndef TEXTURESYSTEM_HPP_
#define TEXTURESYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/Transform.hpp"
#include "Components/Window.hpp"

namespace is::systems {

    class TextureSystem: public is::ecs::ASystem {
        public:
            TextureSystem() = default;
            ~TextureSystem() override = default;

            TextureSystem(const TextureSystem &) = default;
            TextureSystem &operator=(const TextureSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}

#endif /* !TEXTURE_HPP_ */

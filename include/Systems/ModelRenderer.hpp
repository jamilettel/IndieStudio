/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef MODELRENDERERSYSTEM_HPP_
#define MODELRENDERERSYSTEM_HPP_

#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <climits>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/ModelRenderer.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"

namespace is::systems {

    class ModelRendererSystem : public is::ecs::ASystem {
        public:
            ModelRendererSystem() = default;
            ~ModelRendererSystem() override = default;

            ModelRendererSystem(const ModelRendererSystem &) = default;
            ModelRendererSystem &operator=(const ModelRendererSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };

}

#endif /* !ModelRendererSystem_HPP_ */

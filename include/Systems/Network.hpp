/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#ifndef SystemNetworkSystem_HPP_
#define SystemNetworkSystem_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <climits>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Network.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"
#include "Components/ModelRenderer.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

namespace is::systems {

    class NetworkSystem : public is::ecs::ASystem {
        public:
            NetworkSystem() = default;
            ~NetworkSystem() override = default;

            NetworkSystem(const NetworkSystem &) = default;
            NetworkSystem &operator=(const NetworkSystem &) = default;

            void awake() override;
            void start() override;
        void extracted();
        
        void update() override;
            void stop() override;
            void onTearDown() override;
        
        size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
        
        void selectHandling(std::shared_ptr<is::components::NetworkComponent> ptr);

        void refreshGameState(std::shared_ptr<is::components::NetworkComponent> ptr);
    };

}

#endif /* !SystemNetworkSystem_HPP_ */

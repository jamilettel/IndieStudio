/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** NetworkInput
*/

#ifndef NetworkINPUTSYSTEM_HPP_
#define NetworkINPUTSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/NetworkInput.hpp"
#include "Components/Network.hpp"

namespace is::systems {

    class NetworkInputSystem: public is::ecs::ASystem {
        public:
            NetworkInputSystem() = default;
            ~NetworkInputSystem() override = default;

            NetworkInputSystem(const NetworkInputSystem &) = default;
            NetworkInputSystem &operator=(const NetworkInputSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
            std::shared_ptr<is::components::NetworkComponent> _network;
    };

}

#endif /* !NetworkINPUTSYSTEM_HPP_ */

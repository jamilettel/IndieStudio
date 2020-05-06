/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <vector>
#include <memory>
#include <algorithm>

#include "ECS/ISystem.hpp"

namespace is::ecs {

    class SystemManager {
        public:
            SystemManager();
            ~SystemManager();

            SystemManager(const SystemManager &) = default;
            SystemManager &operator=(const SystemManager &) = default;

            void addSystem(const std::shared_ptr<ISystem> &system);

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
        private:
            std::vector<std::shared_ptr<ISystem>> _systems;
    };

}

#endif /* !SYSTEMMANAGER_HPP_ */

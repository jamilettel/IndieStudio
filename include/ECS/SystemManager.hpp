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
#include "ECS/ComponentManager.hpp"

namespace is::ecs {

    class SystemManager {
        public:
            SystemManager(std::shared_ptr<ComponentManager> componentManager);
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
            std::shared_ptr<ComponentManager> _componentManager;
    };
}

#endif /* !SYSTEMMANAGER_HPP_ */

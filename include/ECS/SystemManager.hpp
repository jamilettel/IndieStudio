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
#include "ECS/EntityManager.hpp"

namespace is::ecs {

    class SystemManager {
        public:
            SystemManager(const std::shared_ptr<ComponentManager>& componentManager,
                          std::shared_ptr<EntityManager> entityManager);
            ~SystemManager();

            SystemManager(const SystemManager &) = default;
            SystemManager &operator=(const SystemManager &) = default;

            void addSystem(const std::shared_ptr<ISystem> &system);

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        private:
            std::vector<std::shared_ptr<ISystem>> _systems;
            std::shared_ptr<ComponentManager> _componentManager;
            std::shared_ptr<EntityManager> _entityManager;
    };
}

#endif /* !SYSTEMMANAGER_HPP_ */

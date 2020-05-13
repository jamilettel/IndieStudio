/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include <map>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>

#include "ECS/Component.hpp"

namespace is::ecs {

    class ComponentManager {
        public:
            ComponentManager() = default;
            ~ComponentManager() = default;

            ComponentManager(const ComponentManager &) = default;
            ComponentManager &operator=(const ComponentManager &) = default;

            void addComponent(std::shared_ptr<Component> component);
            void removeComponent(std::shared_ptr<Component> &component);

            std::vector<std::shared_ptr<Component>> &getComponentsByType(size_t type);

        protected:
        private:
            std::map<size_t, std::vector<std::shared_ptr<Component>>> _components;
    };

}

#endif /* !COMPONENTMANAGER_HPP_ */

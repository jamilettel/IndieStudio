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

#include "ECS/Component.hpp"

namespace is::ecs {

    class ComponentManager {
        public:
            ComponentManager();
            ~ComponentManager();

            ComponentManager(const ComponentManager &) = default;
            ComponentManager &operator=(const ComponentManager &) = default;

        protected:
        private:
            std::map<std::string, std::vector<std::weak_ptr<Component>>> map;
    };

}

#endif /* !COMPONENTMANAGER_HPP_ */

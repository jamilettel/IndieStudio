/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemManager
*/

#ifndef SYSTEMMANAGER_HPP_
#define SYSTEMMANAGER_HPP_

#include <vector>

#include "ECS/ISystem.hpp"

namespace is::ecs {

    class SystemManager {
        public:
            SystemManager();
            ~SystemManager();

            SystemManager(const SystemManager &) = default;
            SystemManager &operator=(const SystemManager &) = default;

        protected:
        private:
            std::vector<ISystem> _systems;
    };

}

#endif /* !SYSTEMMANAGER_HPP_ */

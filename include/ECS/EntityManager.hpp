/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>

#include "ECS/Entity.hpp"

namespace is::ecs {

    class EntityManager {
        public:
            EntityManager();
            ~EntityManager();

            EntityManager(const EntityManager &) = default;
            EntityManager &operator=(const EntityManager &) = default;


        protected:
        private:
            std::vector<Entity> _entities;
    };

}

#endif /* !ENTITYMANAGER_HPP_ */

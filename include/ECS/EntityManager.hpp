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
            EntityManager() = default;
            ~EntityManager() = default;

            EntityManager(const EntityManager &) = default;
            EntityManager &operator=(const EntityManager &) = default;

            void addEntity(std::shared_ptr<Entity> &entity);
        protected:
        private:
            std::vector<std::shared_ptr<Entity>> _entities;
    };

}

#endif /* !ENTITYMANAGER_HPP_ */

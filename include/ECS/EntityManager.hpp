/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include <vector>
#include <iostream>

#include "ECS/Entity.hpp"
#include "ECS/ComponentManager.hpp"

namespace is::ecs {

    class EntityManager {
        public:
            EntityManager() = default;
            ~EntityManager() = default;

            EntityManager(const EntityManager &) = default;
            EntityManager &operator=(const EntityManager &) = default;

            void addEntity(std::shared_ptr<Entity> &entity);
            void deleteEntities(std::shared_ptr<is::ecs::ComponentManager> &cm);
        
            [[nodiscard]] std::vector<std::shared_ptr<Entity>> getEntities() const;

            bool operator()(std::shared_ptr<is::ecs::Entity> &ent);
        private:
            std::vector<std::shared_ptr<Entity>> _entities;
    };

}

#endif /* !ENTITYMANAGER_HPP_ */

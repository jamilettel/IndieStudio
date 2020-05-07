/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** EntityManager
*/

#include "ECS/EntityManager.hpp"

void is::ecs::EntityManager::addEntity(std::shared_ptr<Entity> &entity)
{
    _entities.push_back(entity);
}

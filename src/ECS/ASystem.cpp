/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ASystem
*/

#include "ECS/ASystem.hpp"

void is::ecs::ASystem::setComponentManager(std::shared_ptr<ComponentManager> componentManager)
{
    _componentManager = componentManager;
}

void is::ecs::ASystem::setEntityManager(std::shared_ptr<EntityManager> entityManager)
{
    _entityManager = entityManager;
}

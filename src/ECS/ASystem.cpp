/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ASystem
*/

#include "ECS/AScene.hpp"
#include "ECS/ASystem.hpp"

using namespace is::ecs;

void ASystem::setComponentManager(std::shared_ptr<ComponentManager> componentManager)
{
    _componentManager = componentManager;
}

void ASystem::setEntityManager(std::shared_ptr<EntityManager> entityManager)
{
    _entityManager = entityManager;
}

std::shared_ptr<Entity> &ASystem::initRuntimeEntity(std::shared_ptr<Entity> &&entity, bool keep)
{
    for (auto &elem : entity->getComponents())
        _componentManager->addComponent(elem);
    _entityManager->addEntity(entity);
    if (keep)
        AScene::saveEntity(entity);
    return (entity);
}

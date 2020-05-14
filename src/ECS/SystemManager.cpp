/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemManager
*/

#include "ECS/SystemManager.hpp"

#include <utility>

is::ecs::SystemManager::SystemManager(const std::shared_ptr<ComponentManager>& componentManager,
    std::shared_ptr<EntityManager> entityManager) :
_componentManager(componentManager),
_entityManager(std::move(entityManager))
{
    std::cout << "SYSTEM : " << componentManager.get() << std::endl; 
}

is::ecs::SystemManager::~SystemManager()
= default;

void is::ecs::SystemManager::addSystem(const std::shared_ptr<is::ecs::ISystem> &system)
{
    system->setComponentManager(_componentManager);
    system->setEntityManager(_entityManager);
    _systems.push_back(system);
}

void is::ecs::SystemManager::awake()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
        system->awake();
    });
}

void is::ecs::SystemManager::start()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
        system->start();
    });
}

void is::ecs::SystemManager::update()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
            system->update();
    });
}

void is::ecs::SystemManager::stop()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
        system->stop();
    });
}

void is::ecs::SystemManager::onTearDown()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
        system->onTearDown();
    });
}


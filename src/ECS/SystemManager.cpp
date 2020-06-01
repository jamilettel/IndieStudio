/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemManager
*/

#include "ECS/SystemManager.hpp"

using namespace is::ecs;

SystemManager::SystemManager(const std::shared_ptr<ComponentManager>& componentManager,
    std::shared_ptr<EntityManager> entityManager) :
_componentManager(componentManager),
_entityManager(std::move(entityManager))
{
    std::cout << "SYSTEM : " << componentManager.get() << std::endl; 
}

SystemManager::~SystemManager()
= default;

void SystemManager::addSystem(const std::shared_ptr<ISystem> &system)
{
    system->setComponentManager(_componentManager);
    system->setEntityManager(_entityManager);
    _systems.push_back(system);
}

void SystemManager::awake()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
        system->awake();
    });
}

void SystemManager::start()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
        system->start();
    });
}

void SystemManager::update()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
            system->update();
    });
}

void SystemManager::stop()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
        system->stop();
    });
}

void SystemManager::onTearDown()
{
    std::for_each(_systems.begin(), _systems.end(), [](std::shared_ptr<ISystem> &system){
        system->onTearDown();
    });
    _systems.clear();
}


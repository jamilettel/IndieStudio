/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AScene
*/

#include "ECS/AScene.hpp"
#include "Game.hpp"

std::shared_ptr<is::ecs::EntityManager> is::ecs::AScene::_entitySaver = std::make_shared<is::ecs::EntityManager>();

is::ecs::AScene::AScene(is::ecs::Scenes sceneID) : _sceneID(sceneID)
{
}

void is::ecs::AScene::initEntity(std::shared_ptr<Entity> &&entity)
{
    for (auto &elem : entity->getComponents()) {
        _componentManager->addComponent(elem);
    }
    _entityManager->addEntity(entity);
}
void is::ecs::AScene::initEntity(std::shared_ptr<Entity> &&entity, bool dontDestroyOnLoad)
{
    for (auto &elem : entity->getComponents())
        _componentManager->addComponent(elem);
    _entityManager->addEntity(entity);
    if (dontDestroyOnLoad)
        _entitySaver->addEntity(entity);
}

void is::ecs::AScene::initStaticEntities()
{
    for (auto ent : _entitySaver->getEntities())
    {
        if (!_entityManager->operator()(ent)) {
            initEntity(std::shared_ptr(ent));
        }
    }
}

void is::ecs::AScene::awake()
{
    std::cout << "first ent " << _entityManager->getEntities().size() << std::endl;
    initSystems();
    initEntities();
    initStaticEntities();
    _systemManager->awake();
    for (auto &ent : _entityManager->getEntities())
        ent->setInit(true);
}

void is::ecs::AScene::start()
{
    _systemManager->start();
    std::cout << "second ent " << _entityManager->getEntities().size() << std::endl;
}

void is::ecs::AScene::update()
{
    _systemManager->update();
    _entityManager->deleteEntities(_componentManager);
}

void is::ecs::AScene::stop()
{
    deleteNonStaticEntities();
    _systemManager->stop();
}

void is::ecs::AScene::onTearDown()
{
    _systemManager->onTearDown();
}

void is::ecs::AScene::deleteNonStaticEntities()
{
    for (auto ent : _entityManager->getEntities())
    {
        if (!_entitySaver->operator()(ent))
            ent->setDelete(true);
    }
    _entityManager->deleteEntities(_componentManager);
}

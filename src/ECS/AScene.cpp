/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AScene
*/

#include "ECS/AScene.hpp"

using namespace is::ecs;

std::shared_ptr<EntityManager> AScene::_entitySaver = std::make_shared<EntityManager>();

AScene::AScene(Scenes sceneID) : _sceneID(sceneID)
{
}

std::shared_ptr<Entity> &AScene::initEntity(std::shared_ptr<Entity> &&entity)
{
    for (auto &elem : entity->getComponents()) {
        _componentManager->addComponent(elem);
    }
    _entityManager->addEntity(entity);
    return (entity);
}

std::shared_ptr<Entity> &AScene::initEntity(std::shared_ptr<Entity> &&entity, bool dontDestroyOnLoad)
{
    for (auto &elem : entity->getComponents())
        _componentManager->addComponent(elem);
    if (dontDestroyOnLoad)
        _entitySaver->addEntity(entity);
    _entityManager->addEntity(entity);
    return (entity);
}

void AScene::initStaticEntities()
{
    for (auto ent : _entitySaver->getEntities())
    {
        if (!_entityManager->operator()(ent)) {
            initEntity(std::shared_ptr(ent));
        }
    }
}

void AScene::awake()
{
    initSystems();
    initStaticEntities();
    initEntities();
    _systemManager->awake();
}

void AScene::start()
{
    _systemManager->start();
    for (auto &ent : _entityManager->getEntities())
        ent->setInit(true);
}

void AScene::update()
{
    _systemManager->update();
    _entityManager->deleteEntities(_componentManager);
}

void AScene::stop()
{
    deleteNonStaticEntities();
    _systemManager->stop();
}

void AScene::onTearDown()
{
    _systemManager->onTearDown();
}

void AScene::deleteNonStaticEntities()
{
    for (auto ent : _entityManager->getEntities())
    {
        if (!_entitySaver->operator()(ent))
            ent->setDelete(true);
    }
    _entityManager->deleteEntities(_componentManager);
}

void AScene::saveEntity(std::shared_ptr<Entity> &e)
{
    _entitySaver->addEntity(e);
}

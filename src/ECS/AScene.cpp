/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** AScene
*/

#include "ECS/AScene.hpp"

void is::ecs::AScene::awake()
{
    initSystems();
    _systemManager.awake();
}

void is::ecs::AScene::start()
{
    _systemManager.start();
}

void is::ecs::AScene::update()
{
    _systemManager.update();
}

void is::ecs::AScene::stop()
{
    _systemManager.stop();
}

void is::ecs::AScene::onTearDown()
{
    _systemManager.onTearDown();
}


/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#include "Prefabs/GlobalPrefabs.hpp"

std::shared_ptr<is::ecs::Entity> prefabs::GlobalPrefabs::createGlobalPrefab()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ComponentWindow>(e);
    e->addComponent<ComponentCamera>(e);
    return (e);
}

std::shared_ptr<is::ecs::Entity> prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    e->addComponent<ComponentModelRenderer>(e, "/Users/tblt/Development/epitech/TEK2/OOP_indie_studio_2019/resources/Prop_Block_Brick.obj", 0);
    return (e);
}

std::shared_ptr<is::ecs::Entity> prefabs::GlobalPrefabs:: createPlayer()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::TransformComponent>(e);
    e->addComponent<ComponentCharacterController>(e);
    e->addComponent<ComponentModelRenderer>(e, "/Users/tblt/Development/epitech/TEK2/OOP_indie_studio_2019/resources/Robot.obj", 0);
    return (e);
}


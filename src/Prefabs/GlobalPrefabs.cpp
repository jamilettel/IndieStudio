/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#include "Prefabs/GlobalPrefabs.hpp"

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createGlobalPrefab()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::ComponentWindow>(e, "Indie Studio");
    e->addComponent<is::components::ComponentCamera>(e, "MainCamera", "Indie Studio", core::vector3df(-20, 20, 0), core::vector3df(1, -1, 0));
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    e->addComponent<is::components::ComponentModelRenderer>(e, "../resources/Prop_Block_Brick.obj", "Indie Studio");
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs:: createPlayer()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::TransformComponent>(e);
    e->addComponent<is::components::ComponentCharacterController>(e, "Indie Studio", 0.01);
    e->addComponent<is::components::ComponentModelRenderer>(e, "../resources/Robot.obj", "Indie Studio");
    return (e);
}

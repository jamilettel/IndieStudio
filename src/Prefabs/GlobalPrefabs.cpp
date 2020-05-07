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
    e->addComponent<is::components::ComponentLight>(e, "Indie Studio", core::vector3df(-100, 100, 0), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 500.0f);
    e->addComponent<is::components::ComponentCamera>(e, "MainCamera", "Indie Studio", core::vector3df(-15, 15, 0), core::vector3df(1, -10, 0));
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    e->addComponent<is::components::ColliderComponent>(e, true, *e->getComponent<is::components::TransformComponent>()->get());
    e->addComponent<is::components::ComponentModelRenderer>(e, "../resources/Prop_Block_Brick.obj", "Indie Studio");
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs:: createPlayer()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<is::components::TransformComponent>(e);
    e->addComponent<is::components::ColliderComponent>(e, true, *e->getComponent<is::components::TransformComponent>()->get());
    e->addComponent<is::components::MovementComponent>(e,
                                                       *e->getComponent<is::components::TransformComponent>()->get(),
                                                       *e->getComponent<is::components::ColliderComponent>()->get());
    e->addComponent<is::components::ComponentCharacterController>(e, "Indie Studio", 0.2);
    e->addComponent<is::components::ComponentModelRenderer>(e, "../resources/Robot.obj", "Indie Studio");
    return (e);
}

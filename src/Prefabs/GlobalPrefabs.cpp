/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#include "Prefabs/GlobalPrefabs.hpp"

#ifdef __APPLE__
    #define RESSOURCE(str) std::string(std::string("../resources/") + std::string(str))
#else
    #define RESSOURCE(str) std::string(std::string("./resources/") + std::string(str))
#endif

using namespace is::components;

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createGlobalPrefab()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<ComponentAudio>(e, RESSOURCE("lol.wav"), MUSIC, true);
    e->addComponent<ComponentWindow>(e, "Indie Studio");
    e->addComponent<ComponentLight>(e, "Indie Studio", core::vector3df(-100, 100, 0), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 500.0f);
    e->addComponent<ComponentCamera>(e, "MainCamera", "Indie Studio", core::vector3df(-15, 27, 0), core::vector3df(-3, 0, 0));
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ComponentModelRenderer>(e, RESSOURCE("Prop_Block_Brick.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs:: createPlayer()
{
    auto e = std::make_shared<is::ecs::Entity>();

    TransformComponent &transform = e->addComponent<TransformComponent>(e);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    MovementComponent &movement = e->addComponent<MovementComponent>(
        e,
        transform,
        collider
    );
    ComponentAudio &audio = e->addComponent<is::components::ComponentAudio>(
        e,
        RESSOURCE("footstep.wav"),
        is::components::SOUND
    );
    e->addComponent<ComponentCharacterController>(
        e,
        transform,
        movement,
        audio,
        "Indie Studio",
        0.2,
        3
    );
    e->addComponent<ComponentModelRenderer>(e, RESSOURCE("Robot.obj"), "Indie Studio");
    e->addComponent<GravityComponent>(e, movement);
    transform.position.Y = 10;
    return (e);
}

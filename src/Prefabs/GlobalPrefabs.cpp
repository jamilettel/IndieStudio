/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#include "Prefabs/GlobalPrefabs.hpp"

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

using namespace is::components;

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createGlobalPrefab()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<AudioComponent>(e, RESSOURCE("lol.wav"), MUSIC, true);
    e->addComponent<WindowComponent>(e, "Indie Studio");
    e->addComponent<LightComponent>(e, "Indie Studio", core::vector3df(-100, 100, 0), video::SColorf(1.0f, 1.0f, 1.0f, 1.0f), 500.0f);
    e->addComponent<CameraComponent>(e, "MainCamera", "Indie Studio", core::vector3df(-15, 27, 0), core::vector3df(-3, 0, 0));
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::GROUND);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Block_Brick.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createBreakableBlock(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::BRKBL_BLK);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Crate.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createBomb(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::BOMB);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("bomb.obj"), "Indie Studio");
    e->addComponent<BombComponent>(e);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createTestPowerUp(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::BOMB);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(2, 2, 2));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Lollipop.obj"), "Indie Studio");
    e->addComponent<PowerUpComponent>(e);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(is::ecs::Entity::PLAYER);
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs::createFire(irr::core::vector3df position)
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::FIRE);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Block_Pause.obj"), "Indie Studio");
    e->addComponent<FireComponent>(e);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(is::ecs::Entity::GROUND);
    collider.addCollisionWithLayer(is::ecs::Entity::BOMB);
    collider.addCollisionWithLayer(is::ecs::Entity::FIRE);
    return (e);
}

#include <iostream>
void a(std::vector<ColliderComponent *> b) {
    std::cout << "ddd" << std::endl;
}

std::shared_ptr<is::ecs::Entity> is::prefabs::GlobalPrefabs:: createPlayer()
{
    auto e = std::make_shared<is::ecs::Entity>(is::ecs::Entity::PLAYER);

    TransformComponent &transform = e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(3.5, 3.5, 3.5)
        );
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(2, 2, 2)
    );
    MovementComponent &movement = e->addComponent<MovementComponent>(
        e,
        transform,
        collider
    );
    AudioComponent &audio = e->addComponent<is::components::AudioComponent>(
        e,
        RESSOURCE("footstep.wav"),
        is::components::SOUND
    );
    e->addComponent<CharacterControllerComponent>(
        e,
        transform,
        movement,
        audio,
        "Indie Studio",
        0.2
    );
    collider.addCollisionWithLayer(is::ecs::Entity::GROUND);
    collider.addCollisionWithLayer(is::ecs::Entity::BRKBL_BLK);
    collider.addCollisionWithLayer(is::ecs::Entity::POWERUP);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    e->addComponent<GravityComponent>(e, movement);
    transform.position.Y = 10;
    e->addComponent<TimeComponent>(e);
    e->addComponent<ColliderTriggerComponent>(e, collider, a);
    e->addComponent<JumpComponent>(e, movement);
    return (e);
}

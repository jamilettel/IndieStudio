/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** EndGamePrefabs
*/

#include "Prefabs/EndGamePrefabs.hpp"

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

using namespace is::components;
using namespace is::ecs;

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createBackground()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/background.jpg"),
        "Indie Studio"
    );
    e->addComponent<is::components::TransformComponent>(
        e,
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(10, 45, 0)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-10, 10, 10),
        irr::core::vector3df(-70, -90, -10)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}
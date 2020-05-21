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
        "Indie Studio",
        irr::core::vector2di(0),
        irr::core::vector2di(-1)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, 18),
        irr::core::vector3df(0, -120, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer2()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, 6),
        irr::core::vector3df(0, -100, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer3()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, -6),
        irr::core::vector3df(0, -70, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createPlayer4()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<TransformComponent>(
        e,
        irr::core::vector3df(-6, 10, -19),
        irr::core::vector3df(0, -50, -70),
        irr::core::vector3df(0.7, 0.7, 0.7)
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createWindow()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Window.png"),
        "Indie Studio",
        irr::core::vector2di(50, 100),
        irr::core::vector2di(330, 700)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createWindow2()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Window.png"),
        "Indie Studio",
        irr::core::vector2di(430, 100),
        irr::core::vector2di(330, 700)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createWindow3()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Window.png"),
        "Indie Studio",
        irr::core::vector2di(830, 100),
        irr::core::vector2di(330, 700)
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> is::prefabs::EndGamePrefabs::createWindow4()
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>();

    e->addComponent<is::components::TextureComponent>(
        e,
        RESSOURCE("ui/EndGame/Window.png"),
        "Indie Studio",
        irr::core::vector2di(1230, 100),
        irr::core::vector2di(330, 700)
    );
    return (e);
}
/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Gravity
*/

#include "Systems/Gravity.hpp"
#include "Components/Gravity.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void GravitySystem::awake()
{}

void GravitySystem::start()
{}

void GravitySystem::stop()
{}

void GravitySystem::onTearDown()
{}

void GravitySystem::update()
{
    std::vector<std::shared_ptr<Component>> &gravities = _componentManager->getComponentsByType(typeid(GravityComponent).hash_code());

    std::for_each(gravities.begin(), gravities.end(), [](std::shared_ptr<Component> &gravity) {
        GravityComponent *ptr = static_cast<GravityComponent *>(gravity.get());

        if (!ptr->isActive() || ptr->getMovement().isOnTheGround()) {
            ptr->gravity = irr::core::vector3df(0, 0, 0);
            return;
        }
        ptr->getMovement().velocity += ptr->gravity;
        ptr->gravity += irr::core::vector3df(0, -0.1, 0);
    });
}
/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Jump
*/

#include "Systems/Jump.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void is::systems::JumpSystem::awake()
{
}

void is::systems::JumpSystem::start()
{

}

void is::systems::JumpSystem::update()
{
    const auto &components = _componentManager->getComponentsByType(typeid(JumpComponent).hash_code());

    std::for_each(components.begin(), components.end(), [](const auto &gravity) {
        auto *ptr = static_cast<JumpComponent *>(gravity.get());

        if (ptr->isJump()) {
            ptr->setJump(false);
            ptr->jumpForce = irr::core::vector3df(0, 0.5, 0);
            ptr->getMovement().setOnTheGround(false);
        }
        if (!ptr->isJump()) {
            if (ptr->getMovement().isOnTheGround())
                ptr->jumpForce = irr::core::vector3df(0, 0, 0);
            ptr->getMovement().velocity += ptr->jumpForce;
            return;
        }
    });
}

void is::systems::JumpSystem::stop()
{

}

void is::systems::JumpSystem::onTearDown()
{

}

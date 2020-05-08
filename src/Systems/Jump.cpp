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
    std::vector<std::shared_ptr<Component>> &components = _componentManager->getComponentsByType(typeid(JumpComponent).hash_code());

    std::for_each(components.begin(), components.end(), [](std::shared_ptr<Component> &gravity) {
        JumpComponent *ptr = static_cast<JumpComponent *>(gravity.get());

        if (ptr->isJumping()) {
            std::cout << "Jump" << std::endl; 
            ptr->setJump(false);
        }
    });
}

void is::systems::JumpSystem::stop()
{

}

void is::systems::JumpSystem::onTearDown()
{

}
/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Movement
*/

#include "Systems/Movement.hpp"
#include "Components/Movement.hpp"
#include <signal.h>
#include <unistd.h>

using namespace is::system;
using namespace is::components;
using namespace is::ecs;

void MovementSystem::awake()
{

}

void MovementSystem::start()
{

}

void MovementSystem::update()
{
    std::vector<std::shared_ptr<Component>> &colliders =
        _componentManager->getComponentsByType(typeid(MovementComponent).hash_code());

    for (size_t i = 0; i < colliders.size(); i++) {
        MovementComponent *ptr = static_cast<MovementComponent *>(colliders[i].get());

        ptr->getTransform().position += ptr->velocity;
    }
}

void MovementSystem::stop()
{

}

void MovementSystem::onTearDown()
{

}

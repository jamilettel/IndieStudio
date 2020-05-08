/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombermanSystem
*/

#include "Systems/Bomberman.hpp"

using namespace irr;

void is::systems::BombermanSystem::awake()
{

}

void is::systems::BombermanSystem::start()
{

}

void is::systems::BombermanSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::BombermanComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::BombermanComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("BombermanComponent", "Could not get BombermanComponent pointer");
    }
}

void is::systems::BombermanSystem::stop()
{

}

void is::systems::BombermanSystem::onTearDown()
{

}


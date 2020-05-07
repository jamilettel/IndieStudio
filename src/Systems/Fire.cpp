/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FireSystem
*/

#include "Systems/Fire.hpp"

using namespace irr;

void is::systems::FireSystem::awake()
{

}

void is::systems::FireSystem::start()
{

}

void is::systems::FireSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::FireComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::FireComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("FireComponent", "Could not get FireComponent pointer");
        ptr->lifeTime-=0.3;
        if (ptr->lifeTime < 0) {
            std::cout << "ddd" << std::endl;
            ptr->getEntity()->setDelete(true);
        }
    }
}

void is::systems::FireSystem::stop()
{

}

void is::systems::FireSystem::onTearDown()
{

}


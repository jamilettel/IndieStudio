/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombSystem
*/

#include "Systems/Bomb.hpp"

using namespace irr;

void is::systems::BombSystem::awake()
{

}

void is::systems::BombSystem::start()
{

}

void is::systems::BombSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::BombComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::BombComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("BombComponent", "Could not get BombComponent pointer");
        ptr->lifeTime-=0.05;
        if (ptr->lifeTime < 0) {
            std::shared_ptr<is::components::WindowComponent> ptr_window;
            bool windowFound = false;
            for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
                ptr_window = std::dynamic_pointer_cast<is::components::WindowComponent>(wc);
                if (!ptr_window)
                    throw is::exceptions::Exception("CharacterControllerSystem", "Could not get WindowComponent pointer");
                if (ptr_window->windowName == ptr->getEntity()->getComponent<is::components::ModelRendererComponent>()->get()->windowName) {
                    windowFound = true;
                    break;
                }
            }
            if (!windowFound)
                throw is::exceptions::Exception("CharacterControllerSystem", "Could not found window");
            // propagate fire
            for (int i = 0; i < 2 && dropFire(ptr, ptr_window, 0, i + 1); i++);
            for (int i = 0; i < 2 && dropFire(ptr, ptr_window, i + 1, 0); i++);
            for (int i = 0; i < 2 && dropFire(ptr, ptr_window, 0, -(i + 1)); i++);
            for (int i = 0; i < 2 && dropFire(ptr, ptr_window, -(i + 1), 0); i++);
            ptr->lifeTime = 1000000000; // TODO: delete bomb object
        }
    }
}

bool is::systems::BombSystem::dropFire(std::shared_ptr<is::components::BombComponent> ptr,
                                       std::shared_ptr<is::components::WindowComponent> ptr_window,
                                       int x,
                                       int y)
{
    irr::core::vector3df f = ptr->getEntity()->getComponent<is::components::TransformComponent>()->get()->position;
    f.X = ((int)((f.X + 1.5f) / 3) + x - (f.X < 0)) * 3;
    f.Y = 0; // remove for 3d game
    f.Z = ((int)((f.Z + 1.5f) / 3) + y - (f.Z < 0)) * 3;
    auto e = this->initRuntimeEntity(is::prefabs::GlobalPrefabs::createFire(f));
    auto mr = std::dynamic_pointer_cast<is::components::ModelRendererComponent>(*e->getComponent<is::components::ModelRendererComponent>());
    mr->initModelRenderer(ptr_window);
    return (true);
}

void is::systems::BombSystem::stop()
{

}

void is::systems::BombSystem::onTearDown()
{

}


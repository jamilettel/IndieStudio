/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemCharacterController
*/

#include "Systems/CharacterController.hpp"

using namespace irr;

SystemCharacterController::SystemCharacterController()
{
}

SystemCharacterController::~SystemCharacterController()
{
}

void SystemCharacterController::awake()
{
}

void SystemCharacterController::start()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentCharacterController).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentCharacterController>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemCharacterController", "Could not get ComponentCharacterController pointer");

        auto window = _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code()).at(0); // TODO: change
        auto ptr_window = std::dynamic_pointer_cast<ComponentWindow>(window);
        if (!ptr_window)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get ComponentWindow pointer");

        ptr_window->eventManager.addKeyEvent(irr::KEY_KEY_W, [ptr](){
            ptr->move = core::vector3df(1, 0, 0);
            ptr->rotateY = 90;
        });
        ptr_window->eventManager.addKeyEvent(irr::KEY_KEY_S, [ptr](){
            ptr->move = core::vector3df(-1, 0, 0);
            ptr->rotateY = 270;
        });
        ptr_window->eventManager.addKeyEvent(irr::KEY_KEY_A, [ptr](){
            ptr->move = core::vector3df(0, 0, 1);
            ptr->rotateY = 0;
        });
        ptr_window->eventManager.addKeyEvent(irr::KEY_KEY_D, [ptr](){
            ptr->move = core::vector3df(0, 0, -1);
            ptr->rotateY = 180;
        });
    }
}

void SystemCharacterController::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentCharacterController).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentCharacterController>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemCharacterController", "Could not get ComponentCharacterController pointer");
        auto tr = ptr->getEntity()->getComponent<is::components::TransformComponent>();
        if (!tr)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get TransformComponent pointer");
        tr->get()->move(ptr->move * 0.01);
        tr->get()->rotation.Y = ptr->rotateY;
    }
}

void SystemCharacterController::stop()
{

}

void SystemCharacterController::onTearDown()
{

}


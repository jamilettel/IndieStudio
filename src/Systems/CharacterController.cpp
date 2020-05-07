/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemCharacterController
*/

#include "Systems/CharacterController.hpp"

using namespace irr;

void is::systems::SystemCharacterController::awake()
{
}

void is::systems::SystemCharacterController::start()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentCharacterController).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentCharacterController>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemCharacterController", "Could not get ComponentCharacterController pointer");

        std::shared_ptr<is::components::ComponentWindow> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::ComponentWindow).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<is::components::ComponentWindow>(wc);
            if (!ptr_window)
                throw new is::exceptions::Exception("SystemCharacterController", "Could not get ComponentWindow pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw new is::exceptions::Exception("SystemCharacterController", "Could not found window");

        ptr_window->eventManager.addEventKeyPressed(irr::KEY_KEY_W, [ptr](){
            ptr->move = core::vector3df(1, 0, 0);
            ptr->rotateY = 90;
        });
        ptr_window->eventManager.addEventKeyPressed(irr::KEY_KEY_S, [ptr](){
            ptr->move = core::vector3df(-1, 0, 0);
            ptr->rotateY = 270;
        });
        ptr_window->eventManager.addEventKeyPressed(irr::KEY_KEY_A, [ptr](){
            ptr->move = core::vector3df(0, 0, 1);
            ptr->rotateY = 0;
        });
        ptr_window->eventManager.addEventKeyPressed(irr::KEY_KEY_D, [ptr](){
            ptr->move = core::vector3df(0, 0, -1);
            ptr->rotateY = 180;
        });
    }
}

void is::systems::SystemCharacterController::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentCharacterController).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentCharacterController>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemCharacterController", "Could not get ComponentCharacterController pointer");
        auto tr = ptr->getEntity()->getComponent<is::components::TransformComponent>();
        if (!tr)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get TransformComponent pointer");
        tr->get()->move(ptr->move * ptr->playerSpeed);
        tr->get()->rotation.Y = ptr->rotateY;
    }
}

void is::systems::SystemCharacterController::stop()
{

}

void is::systems::SystemCharacterController::onTearDown()
{

}


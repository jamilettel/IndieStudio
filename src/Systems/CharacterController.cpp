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
        auto tr = ptr->getEntity()->getComponent<is::components::TransformComponent>();
        if (!tr)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get TransformComponent pointer");
        auto window = _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code()).at(0); // change
        auto ptr_window = std::dynamic_pointer_cast<ComponentWindow>(window);
        if (!ptr_window)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get ComponentWindow pointer");
        ptr_window->eventManager.addKeyEvent(irr::KEY_KEY_W, [tr](){
            std::cout << "sxcs" << std::endl;
            tr->get()->move(irr::core::vector3df(0.01, 0, 0));
        });
    }
}

void SystemCharacterController::update()
{
    //for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentCharacterController).hash_code())) {
    //    auto ptr = std::dynamic_pointer_cast<ComponentCharacterController>(elem);
    //    if (!ptr)
    //        throw new is::exceptions::Exception("SystemCharacterController", "Could not get ComponentCharacterController pointer");
    //    auto tr = ptr->getEntity()->getComponent<is::components::TransformComponent>();
    //    if (!tr)
    //        throw new is::exceptions::Exception("SystemModelRenderer", "Could not get TransformComponent pointer");
    //    auto window = _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code()).at(0); // change
    //    auto ptr_window = std::dynamic_pointer_cast<ComponentWindow>(window);
    //    if (!ptr_window)
    //        throw new is::exceptions::Exception("SystemModelRenderer", "Could not get ComponentWindow pointer");
    //    tr->get()->move(irr::core::vector3df(0.01, 0, 0));
    //}
}

void SystemCharacterController::stop()
{

}

void SystemCharacterController::onTearDown()
{

}


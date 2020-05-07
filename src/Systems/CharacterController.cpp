/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemCharacterController
*/

#include "Systems/CharacterController.hpp"
#include "Components/Audio.hpp"

using namespace irr;
using namespace is::components;

void is::systems::SystemCharacterController::awake()
{
}

void is::systems::SystemCharacterController::start()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentCharacterController).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentCharacterController>(elem);
        if (!ptr)
            throw is::exceptions::Exception("SystemCharacterController", "Could not get ComponentCharacterController pointer");

        std::shared_ptr<ComponentWindow> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<ComponentWindow>(wc);
            if (!ptr_window)
                throw is::exceptions::Exception("SystemCharacterController", "Could not get ComponentWindow pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw is::exceptions::Exception("SystemCharacterController", "Could not found window");

        ptr_window->eventManager.addEventKeyPressed(irr::KEY_KEY_W, [ptr](){
            ptr->move.X = 1;
        });
        ptr_window->eventManager.addEventKeyReleased(irr::KEY_KEY_W, [ptr](){
            if (ptr->move.X == 1)
                ptr->move.X = 0;
        });
        ptr_window->eventManager.addEventKeyPressed(irr::KEY_KEY_S, [ptr](){
            ptr->move.X = -1;
        });
        ptr_window->eventManager.addEventKeyReleased(irr::KEY_KEY_S, [ptr](){
            if (ptr->move.X == -1)
                ptr->move.X = 0;
        });
        ptr_window->eventManager.addEventKeyPressed(irr::KEY_KEY_A, [ptr](){
            ptr->move.Z = 1;
        });
        ptr_window->eventManager.addEventKeyReleased(irr::KEY_KEY_A, [ptr](){
            if (ptr->move.Z == 1)
                ptr->move.Z = 0;
        });
        ptr_window->eventManager.addEventKeyPressed(irr::KEY_KEY_D, [ptr](){
            ptr->move.Z = -1;
        });
        ptr_window->eventManager.addEventKeyReleased(irr::KEY_KEY_D, [ptr](){
            if (ptr->move.Z == -1)
                ptr->move.Z = 0;
        });
        ptr_window->eventManager.addEventKeyReleased(
            irr::KEY_SPACE,
            [ptr](){
                ptr->jump = true;
            });
    }
}

void is::systems::SystemCharacterController::rotateToAngle(irr::core::vector3df &rotate,
                                                           float angle)
{
    int diff;

    angle = 360 - angle;
    diff = (360 + (int)angle - (int)rotate.Y) % 360;
    if (diff > 180)
        rotate.Y += 15;
    else if (diff < 180)
        rotate.Y -= 15;
}

void is::systems::SystemCharacterController::rotateToDirection(irr::core::vector3df move,
                                                               irr::core::vector3df &rotate)
{
    float angle;

    if (move.X == 0 && move.Z == 0)
        return;
    if (move.X < 0)
        angle = 270 - (atan(move.Z / -move.X) * 180 / M_PI);
    else
        angle = 90 + (atan(move.Z / move.X) * 180 / M_PI);
    rotateToAngle(rotate, angle);
}

void is::systems::SystemCharacterController::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentCharacterController).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentCharacterController>(elem);
        if (!ptr)
            throw is::exceptions::Exception("SystemCharacterController", "Could not get ComponentCharacterController pointer");
        ptr->getMovementComponent().velocity = ptr->move * ptr->playerSpeed;
        rotateToDirection(ptr->move, ptr->getTransform().rotation);
        if (ptr->move.X != 0 || ptr->move.Z != 0)
            ptr->getAudioComponent().toPlay();
    }
}

void is::systems::SystemCharacterController::stop()
{
}

void is::systems::SystemCharacterController::onTearDown()
{
}
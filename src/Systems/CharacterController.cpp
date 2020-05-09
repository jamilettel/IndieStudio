/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterControllerSystem
*/

#include "Systems/CharacterController.hpp"
#include "Components/Audio.hpp"

using namespace irr;
using namespace is::components;

void is::systems::CharacterControllerSystem::awake()
{
}

void is::systems::CharacterControllerSystem::start()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(CharacterControllerComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<CharacterControllerComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not get CharacterControllerComponent pointer");
        auto im = ptr->getEntity()->getComponent<is::components::InputManagerComponent>();
        if (!im)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not found bomberman");
    }
}

void is::systems::CharacterControllerSystem::rotateToAngle(irr::core::vector3df &rotate,
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

void is::systems::CharacterControllerSystem::rotateToDirection(irr::core::vector3df move,
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

void is::systems::CharacterControllerSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(CharacterControllerComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<CharacterControllerComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not get CharacterControllerComponent pointer");
        auto bm = ptr->getEntity()->getComponent<is::components::BombermanComponent>();
        if (!bm)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not found bomberman");
        auto im = ptr->getEntity()->getComponent<is::components::InputManagerComponent>();
        if (!im)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not found bomberman");
        ptr->move.X = im->get()->getInput("MoveVerticalAxis");
        ptr->move.Z = im->get()->getInput("MoveHorizontalAxis");
        
        //  other function
        if (im->get()->getInput("Jump") == 1) {
            std::optional<std::shared_ptr<JumpComponent>> jump = ptr->getEntity()->getComponent<JumpComponent>();
            if (!jump.has_value())
                return;
            jump.value()->setJump(true);
        }

        //other function
        if (im->get()->getInput("DropBomb") == 1) {
            if (ptr->canPlaceBomb) {
                std::shared_ptr<WindowComponent> ptr_window;
                bool windowFound = false;
                for (auto &wc : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
                    ptr_window = std::dynamic_pointer_cast<WindowComponent>(wc);
                    if (!ptr_window)
                        throw is::exceptions::Exception("CharacterControllerSystem", "Could not get WindowComponent pointer");
                    if (ptr_window->windowName == ptr->windowName) {
                        windowFound = true;
                        break;
                    }
                }
                if (!windowFound)
                    throw is::exceptions::Exception("CharacterControllerSystem", "Could not found window");
                auto bm = ptr->getEntity()->getComponent<is::components::BombermanComponent>();
                if (!bm)
                    throw is::exceptions::Exception("CharacterControllerSystem", "Could not found bomberman");
                if (bm->get()->instantBomb + 1 > bm->get()->bombNumber)
                    return;
                bm->get()->instantBomb++;
                auto e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createBomb(ptr->getTransform().position, bm->get()->bombRange, bm.value()));
                auto ptr_mr = std::dynamic_pointer_cast<ModelRendererComponent>(*e->getComponent<ModelRendererComponent>());
                ptr_mr->initModelRenderer(ptr_window);
                ptr->canPlaceBomb = false;
            }
        } else {
            ptr->canPlaceBomb = true;
        }
        ptr->getMovementComponent().velocity = ptr->move * ptr->playerSpeed * bm->get()->speedMult;
        rotateToDirection(ptr->move, ptr->getTransform().rotation);
        if (ptr->move.X != 0 || ptr->move.Z != 0)
            ptr->getAudioComponent().toPlay();
    }
}

void is::systems::CharacterControllerSystem::stop()
{
}

void is::systems::CharacterControllerSystem::onTearDown()
{
}

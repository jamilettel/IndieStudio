/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AIControllerComponent
*/

#include "Components/AIController.hpp"

using namespace is::components;
using namespace is::ecs;

AIControllerComponent::AIControllerComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    InputManagerComponent &inputManager
    ): Component(e), _inputManager(inputManager)
{
    offense = true;
    objective = irr::core::vector2df(0);
    needObjective = true;
    timeBeforeBegin = 1.5f;
}

void AIControllerComponent::deleteComponent()
{}

InputManagerComponent &AIControllerComponent::getInputManager() const
{
    return _inputManager;
}

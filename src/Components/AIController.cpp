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
    static int id = 0;

    _id = id++;
    shortObjective = irr::core::vector2di(0);
    lastShortObjective = irr::core::vector2di(0);
    longObjective = irr::core::vector2di(0);
    timeBeforeBegin = 1.5f;
}

void AIControllerComponent::deleteComponent()
{}

InputManagerComponent &AIControllerComponent::getInputManager() const
{
    return _inputManager;
}

bool AIControllerComponent::operator==(const is::components::AIControllerComponent &ai) const
{
    return (_id == ai._id);
}
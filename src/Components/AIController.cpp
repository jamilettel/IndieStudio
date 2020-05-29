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
    InputManagerComponent &inputManager,
    int level
) : Component(e), _inputManager(inputManager), _level(level)
{
    static int id = 0;

    if (level < 1 || level > 5)
        throw is::exceptions::ECSException("Invalid argument ai controller component");
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

int AIControllerComponent::getLevel() const noexcept
{
    return (_level);
}
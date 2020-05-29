/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIControllerLevel4
*/

#include "Systems/AIControllerLevel4.hpp"

using namespace is::ecs;
using namespace is::exceptions;
using namespace is::systems;

void AIControllerLevel4System::awake()
{
    std::vector<std::shared_ptr<Component>> &aiComponents =
        _componentManager->getComponentsByType(typeid(AIControllerComponent).hash_code());

    for (std::shared_ptr<Component> &component: aiComponents) {
        if (component->getEntity()->isInit())
            continue;
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());

        if (ai.getLevel() != 4)
            continue;

        ai.getInputManager().addValue("MoveHorizontalAxis", 0);
        ai.getInputManager().addValue("MoveVerticalAxis", 0);
        ai.getInputManager().addValue("Jump", 0);
        ai.getInputManager().addValue("DropBomb", 0);
    }

    // _mapFunctionState[AIControllerComponent::AIState::NONE] = &AIControllerLevel4System::noneState;
    // _mapFunctionState[AIControllerComponent::AIState::ESCAPE_EXPLOSION] = &AIControllerLevel4System::escapeExplosionState;
    // _mapFunctionState[AIControllerComponent::AIState::PUT_BOMB] = &AIControllerLevel4System::putBombState;
    // _mapFunctionState[AIControllerComponent::AIState::WAITING] = &AIControllerLevel4System::waitingState;
}

void AIControllerLevel4System::start()
{
    std::vector<std::shared_ptr<Component>> &time =
        _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());

    if (!time.size())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<TimeComponent *>(time[0].get()));
}

void AIControllerLevel4System::update()
{}

void AIControllerLevel4System::stop()
{}

void AIControllerLevel4System::onTearDown()
{}
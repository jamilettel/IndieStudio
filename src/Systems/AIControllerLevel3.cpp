/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIControllerLevel3
*/

#include "Systems/AIControllerLevel3.hpp"

using namespace is::ecs;
using namespace is::exceptions;
using namespace is::systems;

void AIControllerLevel3System::awake()
{
    std::vector<std::shared_ptr<Component>> &aiComponents =
        _componentManager->getComponentsByType(typeid(AIControllerComponent).hash_code());

    for (std::shared_ptr<Component> &component: aiComponents) {
        if (component->getEntity()->isInit())
            continue;
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());

        if (ai.getLevel() != 3)
            continue;

        ai.getInputManager().addValue("MoveHorizontalAxis", 0);
        ai.getInputManager().addValue("MoveVerticalAxis", 0);
        ai.getInputManager().addValue("Jump", 0);
        ai.getInputManager().addValue("DropBomb", 0);
    }

    _mapFunctionState[AIControllerComponent::AIState::NONE] = &AIControllerLevel3System::noneState;
    _mapFunctionState[AIControllerComponent::AIState::ESCAPE_EXPLOSION] = &AIControllerLevel3System::escapeExplosionState;
    _mapFunctionState[AIControllerComponent::AIState::PUT_BOMB] = &AIControllerLevel3System::putBombState;
    _mapFunctionState[AIControllerComponent::AIState::WAITING] = &AIControllerLevel3System::waitingState;
}

void AIControllerLevel3System::start()
{
    std::vector<std::shared_ptr<Component>> &time =
        _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());

    if (!time.size())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<TimeComponent *>(time[0].get()));
}

void AIControllerLevel3System::stop()
{}

void AIControllerLevel3System::onTearDown()
{}

void AIControllerLevel3System::update()
{
    std::vector<std::shared_ptr<Component>> &aiComponents =
        _componentManager->getComponentsByType(typeid(AIControllerComponent).hash_code());
    std::vector<std::shared_ptr<Component>> &characterComponents =
        _componentManager->getComponentsByType(typeid(CharacterControllerComponent).hash_code());
    std::vector<std::shared_ptr<Component>> &trComponents =
        _componentManager->getComponentsByType(typeid(TransformComponent).hash_code());
    std::vector<std::vector<is::ecs::Entity::Layer>> map(_mapX, std::vector<is::ecs::Entity::Layer>(_mapY, is::ecs::Entity::Layer::DEFAULT)); // get infos from map for size

    // create a map of actual positions
    for (std::shared_ptr<Component> &component: trComponents) {
        TransformComponent &tr = *static_cast<TransformComponent *>(component.get());
        if (tr.position.Y < 0)
            continue;
        int x = (tr.position.X) / 3 + (int)(_mapX / 2);
        int y = (tr.position.Z) / 3 + (int)(_mapY / 2);
        if (!AIControllerUtils::isValid(irr::core::vector2di(x, y), map))
            continue;
        map[x][y] = tr.getEntity()->layer;
    }

    for (std::shared_ptr<Component> &component: aiComponents) {
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());

        if (ai.getLevel() != 3)
            continue;
        ai.timeBeforeBegin -= _time->get().getCurrentIntervalSeconds();
        if (ai.timeBeforeBegin > 0)
            continue;
        
        TransformComponent &tr = *static_cast<TransformComponent *>(ai.getEntity()->getComponent<TransformComponent>()->get());
        irr::core::vector2df aiPos;

        aiPos.X = (tr.position.X + (int)(_mapX * 3 / 2)) / 3;
        aiPos.Y = (tr.position.Z + (int)(_mapY * 3 / 2)) / 3;
        ai.getInputManager().setValue("DropBomb", 0);
        ai.getInputManager().setValue("MoveHorizontalAxis", 0);
        ai.getInputManager().setValue("MoveVerticalAxis", 0);

        (this->*(_mapFunctionState)[ai.state])(ai, aiPos, map, characterComponents);
    }
}

void AIControllerLevel3System::noneState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    
}

void AIControllerLevel3System::escapeExplosionState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{

}

void AIControllerLevel3System::putBombState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{

}

// WAITING STATE
void AIControllerLevel3System::waitingState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{

}

// GET POWERUP STATE
void AIControllerLevel3System::getPowerupState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{

}

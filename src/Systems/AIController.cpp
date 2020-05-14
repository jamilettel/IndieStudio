/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIController
*/

#include "Systems/AIController.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void AIControllerSystem::awake()
{
     std::vector<std::shared_ptr<Component>> &aiComponents =
        _componentManager->getComponentsByType(typeid(AIControllerComponent).hash_code());

    for (std::shared_ptr<Component> &component: aiComponents) {
        if (component->getEntity()->isInit())
            continue;
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());
        
        ai.getInputManager().addValue("MoveHorizontalAxis", 0);
        ai.getInputManager().addValue("MoveVerticalAxis", 0);
        ai.getInputManager().addValue("Jump", 0);
        ai.getInputManager().addValue("DropBomb", 0);
    }

    _mapFunctionState[AIControllerComponent::AIState::NONE] = &AIControllerSystem::noneState;
    _mapFunctionState[AIControllerComponent::AIState::ESCAPE_EXPLOSION] = &AIControllerSystem::escapeExplosionState;
    _mapFunctionState[AIControllerComponent::AIState::PUT_BOMB] = &AIControllerSystem::putBombState;
    _mapFunctionState[AIControllerComponent::AIState::WAITING] = &AIControllerSystem::waitingState;
}

void AIControllerSystem::start()
{
    std::vector<std::shared_ptr<Component>> &time =
        _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());

    if (!time.size())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<TimeComponent *>(time[0].get()));
}

void AIControllerSystem::stop()
{}

void AIControllerSystem::onTearDown()
{}

void AIControllerSystem::update()
{
    std::vector<std::shared_ptr<Component>> &aiComponents =
        _componentManager->getComponentsByType(typeid(AIControllerComponent).hash_code());
    std::vector<std::shared_ptr<Component>> &trComponents =
        _componentManager->getComponentsByType(typeid(TransformComponent).hash_code());
    int mapX = 13, mapY = 15;
    std::vector<std::vector<is::ecs::Entity::Layer>> map(mapX, std::vector<is::ecs::Entity::Layer>(mapY, is::ecs::Entity::Layer::DEFAULT)); // get infos from map for size

    // create a map of actual positions
    for (std::shared_ptr<Component> &component: trComponents) {
        TransformComponent &tr = *static_cast<TransformComponent *>(component.get());
        if (tr.position.Y < 0)
            continue;
        map[(tr.position.X) / 3 + (int)(mapX / 2)][(tr.position.Z) / 3 + (int)(mapY / 2)] = tr.getEntity()->layer;
    }

    for (std::shared_ptr<Component> &component: aiComponents) {
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());
        
        ai.timeBeforeBegin -= _time->get().getCurrentIntervalSeconds();
        if (ai.timeBeforeBegin > 0)
            continue;
        
        TransformComponent &tr = *static_cast<TransformComponent *>(ai.getEntity()->getComponent<TransformComponent>()->get());
        irr::core::vector2df aiPos;
        
        aiPos.X = (tr.position.X + (int)(mapX * 3 / 2)) / 3;
        aiPos.Y = (tr.position.Z + (int)(mapY * 3 / 2)) / 3;
        ai.getInputManager().setValue("DropBomb", 0);
        ai.getInputManager().setValue("MoveHorizontalAxis", 0);
        ai.getInputManager().setValue("MoveVerticalAxis", 0);

        (this->*(_mapFunctionState)[ai.state])(ai, aiPos, map);
    }
}


/****************************\
*
* NONE STATE
*
*****************************/

void AIControllerSystem::noneState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    // std::cout << "NONE STATE" << std::endl;
    ai.lastShortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
    ai.shortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
    setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
}

void AIControllerSystem::setNewLongObjective(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const
{
    std::vector<irr::core::vector2di> lastMove;

    if (findBombEmplacement(ai, aiPos, map)) {
        std::cout << "FIND EMPLACEMENT FOR BOMB" << std::endl;
        std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
        std::cout << "Escape (after pose the bomb) to X: " << ai.posToEscape.X << ", Y: " << ai.posToEscape.Y << std::endl;

        AStarAlgorithm<is::ecs::Entity::Layer> astar(map, std::pair<int, int>(aiPos.X, aiPos.Y), std::pair<int, int>(ai.longObjective.X, ai.longObjective.Y), [this](const is::ecs::Entity::Layer &layter) ->bool {
            return (!isAirBlock(layter));
        });
        astar.searchPath();
        std::optional<std::pair<int, int>> pos;
        ai.path.clear();
        while ((pos = astar.getNextPos()).has_value()) {
            ai.path.emplace_back(pos.value());
        }

        setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    } else {
        // std::cout << "CANT FIND EMPLACEMENT FOR BOMB" << std::endl;
        ai.state = AIControllerComponent::NONE;
    }
}

bool AIControllerSystem::canHideFromExplosion(
    AIControllerComponent &ai,
    const irr::core::vector2di &pos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map
) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};
    std::vector<irr::core::vector2di> successors;

    successors.emplace_back(irr::core::vector2di(pos.X + 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y + 1));
    successors.emplace_back(irr::core::vector2di(pos.X - 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y - 1));
    while (successors.size() != 0) {
        irr::core::vector2di newPos = successors[0];

        successors.erase(successors.begin());
        if (!isValid(newPos, map) || !isAirBlock(map[newPos.X][newPos.Y]))
            continue;
        if (newPos.X != pos.X && newPos.Y != pos.Y) {
            ai.posToEscape = newPos;
            return true;
        } else {
            if (pos.X - newPos.X >= 0)
                successors.emplace_back(irr::core::vector2di(newPos.X - 1, newPos.Y));
            if (pos.X - newPos.X <= 0)
                successors.emplace_back(irr::core::vector2di(newPos.X + 1, newPos.Y));
            if (pos.Y - newPos.Y >= 0)
                successors.emplace_back(irr::core::vector2di(newPos.X, newPos.Y - 1));
            if (pos.Y - newPos.Y <= 0)
                successors.emplace_back(irr::core::vector2di(newPos.X, newPos.Y + 1));
        }
    }
    return false;
}

bool AIControllerSystem::bombPosIsUseful(const irr::core::vector2di &bombPos, const std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};

    for (int i = 0; i < 4; i++) {
        irr::core::vector2di newPos(bombPos.X + dirX[i], bombPos.Y + dirY[i]);

        if (map[bombPos.X + dirX[i]][bombPos.Y + dirY[i]] == is::ecs::Entity::Layer::BRKBL_BLK)
            return (true);
    }
    return (false);
}

bool AIControllerSystem::findBombEmplacement(
    AIControllerComponent &ai,
    const irr::core::vector2di &pos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map
) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};
    std::vector<irr::core::vector2di> successors;

    successors.emplace_back(irr::core::vector2di(pos.X + 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y + 1));
    successors.emplace_back(irr::core::vector2di(pos.X - 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y - 1));
    while (successors.size() != 0) {
        irr::core::vector2di newPos = successors[0];

        successors.erase(successors.begin());
        if (!isValid(newPos, map) || !isAirBlock(map[newPos.X][newPos.Y]))
            continue;
        if (bombPosIsUseful(newPos, map) && canHideFromExplosion(ai, newPos, map)) {
            ai.state = AIControllerComponent::AIState::PUT_BOMB;
            ai.longObjective = newPos;
            return true;
        } else {
            if (pos.X - newPos.X >= 0)
                successors.emplace_back(irr::core::vector2di(newPos.X - 1, newPos.Y));
            if (pos.X - newPos.X <= 0)
                successors.emplace_back(irr::core::vector2di(newPos.X + 1, newPos.Y));
            if (pos.Y - newPos.Y >= 0)
                successors.emplace_back(irr::core::vector2di(newPos.X, newPos.Y - 1));
            if (pos.Y - newPos.Y <= 0)
                successors.emplace_back(irr::core::vector2di(newPos.X, newPos.Y + 1));
        }
    }
    return false;
}


/****************************\
*
* ESCAPE EXPLOSION STATE
*
*****************************/

void AIControllerSystem::escapeExplosionState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map
) const
{
    // std::cout << "ESCAPE EXPLOSION STATE" << std::endl;
    moveAI(ai, aiPos);
    if (hasReachedObjective(ai, aiPos)) {
        if (ai.shortObjective == ai.longObjective) {
            ai.state = AIControllerComponent::NONE;
            std::cout << "NONE" << std::endl;
            ai.timeBeforeBegin = 3.5f;
            ai.lastShortObjective = ai.shortObjective;
            ai.getInputManager().setValue("MoveVerticalAxis", 0);
            ai.getInputManager().setValue("MoveHorizontalAxis", 0);
            return;
        }
        setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    }
}


/****************************\
*
* PUT BOMB STATE
*
*****************************/

void AIControllerSystem::putBombState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    // std::cout << "PUT BOMB STATE" << std::endl;

    moveAI(ai, aiPos);
    if (hasReachedObjective(ai, aiPos)) {
        if (ai.shortObjective == ai.longObjective) {
            ai.getInputManager().setValue("DropBomb", 1);
            ai.state = AIControllerComponent::ESCAPE_EXPLOSION;
            ai.longObjective = ai.posToEscape;
            std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
            ai.lastShortObjective = ai.shortObjective;

            AStarAlgorithm<is::ecs::Entity::Layer> astar(map, std::pair<int, int>(aiPos.X, aiPos.Y), std::pair<int, int>(ai.longObjective.X, ai.longObjective.Y), [this](const is::ecs::Entity::Layer &layter) ->bool {
                return (!isAirBlock(layter));
            });
            astar.searchPath();
            std::optional<std::pair<int, int>> pos;
            ai.path.clear();
            while ((pos = astar.getNextPos()).has_value()) {
                ai.path.emplace_back(pos.value());
            }
        }
        setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    }
}


/****************************\
*
* WAITING STATE
*
*****************************/

void AIControllerSystem::waitingState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    // std::cout << "WAITING STATE" << std::endl;
    ai.getInputManager().setValue("MoveVerticalAxis", 0);
    ai.getInputManager().setValue("MoveHorizontalAxis", 0);
}


/****************************\
*
* UTILS
*
*****************************/

void AIControllerSystem::moveAI(AIControllerComponent &ai, irr::core::vector2df &aiPos) const
{
    if (ai.state == AIControllerComponent::WAITING || ai.state == AIControllerComponent::NONE) {
        std::cout << "STOP" << std::endl;
        ai.state = AIControllerComponent::NONE;
        return;
    }
    if (ai.lastShortObjective.Y > ai.shortObjective.Y)
        ai.getInputManager().setValue("MoveHorizontalAxis", -1);
    else if (ai.lastShortObjective.Y < ai.shortObjective.Y)
        ai.getInputManager().setValue("MoveHorizontalAxis", 1);
    else if (ai.lastShortObjective.X > ai.shortObjective.X)
        ai.getInputManager().setValue("MoveVerticalAxis", -1);
    else if (ai.lastShortObjective.X < ai.shortObjective.X)
        ai.getInputManager().setValue("MoveVerticalAxis", 1);
}

bool AIControllerSystem::hasReachedObjective(AIControllerComponent &ai, irr::core::vector2df &aiPos) const noexcept
{
    return (aiPos.X - (0.3333f) >= ai.shortObjective.X &&
        aiPos.X - (0.3333f) <= ai.shortObjective.X + 1 &&
        aiPos.X + (0.3333f) >= ai.shortObjective.X &&
        aiPos.X + (0.3333f) <= ai.shortObjective.X + 1 &&
        aiPos.Y - (0.3333f) >= ai.shortObjective.Y &&
        aiPos.Y - (0.3333f) <= ai.shortObjective.Y + 1 &&
        aiPos.Y + (0.3333f) >= ai.shortObjective.Y &&
        aiPos.Y + (0.3333f) <= ai.shortObjective.Y + 1);
}

bool AIControllerSystem::isInDanger(irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const
{
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t a = 0; a < map[i].size(); a++) {
            if (map[i][a] != is::ecs::Entity::Layer::BOMB) {
                continue;
            }
            if (i == aiPos.X || a == aiPos.Y) {
                return (true);
            }
        }
    }
    return (false);
}

void AIControllerSystem::setNewShortObjective(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};

    if (!ai.path.size())
        return;
    ai.lastShortObjective = ai.shortObjective;
    ai.shortObjective.X = ai.path[0].first;
    ai.shortObjective.Y = ai.path[0].second;
    ai.path.erase(ai.path.begin());
    std::cout << "New Short objective X :" << ai.shortObjective.X << ", Y:" << ai.shortObjective.Y << std::endl;
}

bool AIControllerSystem::isAirBlock(is::ecs::Entity::Layer layer) const
{
    return (layer == is::ecs::Entity::Layer::DEFAULT ||
        layer == is::ecs::Entity::Layer::PLAYER ||
        layer == is::ecs::Entity::Layer::POWERUP);
}

bool AIControllerSystem::isValid(const irr::core::vector2di &pos, const std::vector<std::vector<is::ecs::Entity::Layer>> &map) const noexcept
{
    if (map.size() == 0)
        return (false);
    return (pos.X >= 0 && pos.X < map.size() && pos.Y >= 0 && pos.Y < map[0].size());
}
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
        // std::cout << "FIND EMPLACEMENT FOR BOMB" << std::endl;
        // std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
        // std::cout << "Escape (after pose the bomb) to X: " << ai.posToEscape.X << ", Y: " << ai.posToEscape.Y << std::endl;

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

bool AIControllerSystem::posIsHideFromABomb(const irr::core::vector2di &aiPos, const std::vector<std::vector<is::ecs::Entity::Layer>> &map, const irr::core::vector2di &bombPos) const noexcept
{
    if (aiPos.X != bombPos.X && aiPos.Y != bombPos.Y)
        return (true);
    if (aiPos.X == bombPos.X && aiPos.Y == bombPos.Y)
        return (false);
    if (aiPos.X == bombPos.X) {
        int incr = (bombPos.Y < aiPos.Y ? -1 : 1);

        for (int tmp = aiPos.Y; tmp != bombPos.Y; tmp += incr) {
            if (layerIsABlock(map[bombPos.X][tmp]))
                return (true);
        }
        return (false);
    } else if (aiPos.Y == bombPos.Y) {
        int incr = (bombPos.X < aiPos.X ? -1 : 1);

        for (int tmp = aiPos.X; tmp != bombPos.X; tmp += incr) {
            if (layerIsABlock(map[tmp][bombPos.Y]))
                return (true);
        }
        return (false);
    }
    return (true);
}

bool AIControllerSystem::posIsHideFromBombs(const irr::core::vector2di &aiPos, const std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    int iSize = map.size();

    for (int i = 0; i < iSize; i++) {
        int jSize = map[i].size();
        
        for (int j = 0; j < jSize; j++) {
            if (map[i][j] != is::ecs::Entity::BOMB)
                continue;
            if (!posIsHideFromABomb(aiPos, map, irr::core::vector2di(i, j)))
                return (false);
        }
    }
    return (true);
}

bool AIControllerSystem::canHideFromExplosion(
    AIControllerComponent &ai,
    const irr::core::vector2di &pos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map
) const
{
    std::vector<irr::core::vector2di> successors;
    std::list<irr::core::vector2di> closeList;

    successors.emplace_back(irr::core::vector2di(pos.X + 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y + 1));
    successors.emplace_back(irr::core::vector2di(pos.X - 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y - 1));
    while (successors.size() != 0) {
        irr::core::vector2di newPos = successors[0];

        successors.erase(successors.begin());
        if (std::find_if(closeList.begin(), closeList.end(), [&newPos](const irr::core::vector2di &pos) -> bool {return pos == newPos;}) != closeList.end())
            continue;
        if (!isValid(newPos, map) || !isAirBlock(map[newPos.X][newPos.Y]))
            continue;
        if (posIsHideFromABomb(newPos, map, pos) && posIsHideFromBombs(newPos, map)) {
            ai.posToEscape = newPos;
            return true;
        }
        closeList.emplace_back(newPos);
        successors.emplace_back(irr::core::vector2di(newPos.X - 1, newPos.Y));
        successors.emplace_back(irr::core::vector2di(newPos.X + 1, newPos.Y));
        successors.emplace_back(irr::core::vector2di(newPos.X, newPos.Y - 1));
        successors.emplace_back(irr::core::vector2di(newPos.X, newPos.Y + 1));
    }
    return false;
}

bool AIControllerSystem::bombPosIsUseful(
    const irr::core::vector2di &bombPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const irr::core::vector2di &aiPos
) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};

    for (int i = 0; i < 4; i++) {
        irr::core::vector2di newPos(bombPos.X + dirX[i], bombPos.Y + dirY[i]);

        if (map[bombPos.X + dirX[i]][bombPos.Y + dirY[i]] == is::ecs::Entity::Layer::BRKBL_BLK || bombPosAimForPlayer(bombPos, map, aiPos))
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
    std::vector<irr::core::vector2di> successors;
    std::list<irr::core::vector2di> closeList;

    successors.emplace_back(irr::core::vector2di(pos.X + 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y + 1));
    successors.emplace_back(irr::core::vector2di(pos.X - 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y - 1));
    while (successors.size() != 0) {
        irr::core::vector2di newPos = successors[0];

        successors.erase(successors.begin());
        if (std::find_if(closeList.begin(), closeList.end(), [&newPos](const irr::core::vector2di &pos) -> bool {return pos == newPos;}) != closeList.end())
            continue;
        if (!isValid(newPos, map) || !isAirBlock(map[newPos.X][newPos.Y]))
            continue;
        if (bombPosIsUseful(newPos, map, pos) && canHideFromExplosion(ai, newPos, map)) {
            ai.state = AIControllerComponent::AIState::PUT_BOMB;
            ai.longObjective = newPos;
            return true;
        }
        closeList.emplace_back(newPos);
        successors.emplace_back(irr::core::vector2di(newPos.X - 1, newPos.Y));
        successors.emplace_back(irr::core::vector2di(newPos.X + 1, newPos.Y));
        successors.emplace_back(irr::core::vector2di(newPos.X, newPos.Y - 1));
        successors.emplace_back(irr::core::vector2di(newPos.X, newPos.Y + 1));
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
            ai.state = AIControllerComponent::WAITING;
            ai.lastShortObjective = ai.shortObjective;
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
            ai.bombPos = ai.longObjective;
            ai.state = AIControllerComponent::ESCAPE_EXPLOSION;
            ai.longObjective = ai.posToEscape;
            // std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
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
    if (!posIsHideFromBombs(irr::core::vector2di(aiPos.X, aiPos.Y), map)) {
        // std::cout << "I am not hide" << std::endl;
        if (canHideFromExplosion(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map)) {
            ai.longObjective = ai.posToEscape;
            ai.state = AIControllerComponent::AIState::ESCAPE_EXPLOSION;
            // std::cout << "Hide to position Y: " << ai.longObjective.Y << ", X: " << ai.longObjective.X << std::endl;
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
            return;
        }
        // std::cout << "SHIT I AM DEAD" << std::endl;
    }
    if (map[ai.bombPos.X][ai.bombPos.Y] != is::ecs::Entity::Layer::BOMB)
        ai.state = AIControllerComponent::NONE;
}


/****************************\
*
* UTILS
*
*****************************/

void AIControllerSystem::moveAI(AIControllerComponent &ai, irr::core::vector2df &aiPos) const
{
    if (ai.state == AIControllerComponent::WAITING || ai.state == AIControllerComponent::NONE) {
        // std::cout << "STOP" << std::endl;
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
            if (static_cast<int>(i) == aiPos.X || static_cast<int>(a) == aiPos.Y) {
                return (true);
            }
        }
    }
    return (false);
}

void AIControllerSystem::setNewShortObjective(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    if (!ai.path.size())
        return;
    ai.lastShortObjective = ai.shortObjective;
    ai.shortObjective.X = ai.path[0].first;
    ai.shortObjective.Y = ai.path[0].second;
    ai.path.erase(ai.path.begin());
    // std::cout << "New Short objective X :" << ai.shortObjective.X << ", Y:" << ai.shortObjective.Y << std::endl;
}

bool AIControllerSystem::isAirBlock(is::ecs::Entity::Layer layer) const noexcept
{
    return (layer == is::ecs::Entity::Layer::DEFAULT ||
        layer == is::ecs::Entity::Layer::PLAYER ||
        layer == is::ecs::Entity::Layer::POWERUP);
}

bool AIControllerSystem::isValid(const irr::core::vector2di &pos, const std::vector<std::vector<is::ecs::Entity::Layer>> &map) const noexcept
{
    if (map.size() == 0)
        return (false);
    return (pos.X >= 0 && pos.X < static_cast<int>(map.size()) && pos.Y >= 0 && pos.Y < static_cast<int>(map[0].size()));
}

bool AIControllerSystem::layerIsABlock(const is::ecs::Entity::Layer &layer) const noexcept
{
    return (layer == is::ecs::Entity::Layer::BRKBL_BLK || layer == is::ecs::Entity::Layer::GROUND);
}

bool AIControllerSystem::bombPosAimForPlayer(
    const irr::core::vector2di &bombPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const irr::core::vector2di &aiPos
) const noexcept
{
    int width = map.size();
    int height = map[bombPos.X].size();

    for (int i = bombPos.X; i < width && i - bombPos.X <= 1; i++) {
        if (layerIsABlock(map[i][bombPos.Y]))
            break;
        if (i == aiPos.X && bombPos.Y == aiPos.Y)
            continue;
        if (map[i][bombPos.Y] == is::ecs::Entity::Layer::PLAYER)
            return true;
    }
    for (int i = bombPos.X; i > 0 && bombPos.X - i <= 1; i--) {
        if (layerIsABlock(map[i][bombPos.Y]))
            break;
        if (i == aiPos.X && bombPos.Y == aiPos.Y)
            continue;
        if (map[i][bombPos.Y] == is::ecs::Entity::Layer::PLAYER)
            return true;
    }
    for (int i = bombPos.Y; i < height && i - bombPos.Y <= 1; i++) {
        if (layerIsABlock(map[bombPos.X][i]))
            break;
        if (bombPos.X == aiPos.X && i == aiPos.Y)
            continue;
        if (map[bombPos.X][i] == is::ecs::Entity::Layer::PLAYER)
            return true;
    }
    for (int i = bombPos.Y; i > 0 && bombPos.Y - i <= 1; i--) {
        if (layerIsABlock(map[bombPos.X][i]))
            break;
        if (bombPos.X == aiPos.X && i == aiPos.Y)
            continue;
        if (map[bombPos.X][i] == is::ecs::Entity::Layer::PLAYER)
            return true;
    }
    return (false);
}

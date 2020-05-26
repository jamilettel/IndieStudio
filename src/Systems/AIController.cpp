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
        if (!isValid(irr::core::vector2di(x, y), map))
            continue;
        map[x][y] = tr.getEntity()->layer;
    }

    for (std::shared_ptr<Component> &component: aiComponents) {
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());

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


/****************************\
*
* NONE STATE
*
*****************************/

void AIControllerSystem::noneState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos, 
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<Component>> &aiComponents
) const
{
    // std::cout << "NONE STATE" << std::endl;
    ai.lastShortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
    ai.shortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
    setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map, aiComponents);
}

void AIControllerSystem::setNewLongObjective(
    AIControllerComponent &ai,
    irr::core::vector2di aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    std::vector<irr::core::vector2di> lastMove;
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    if (findBombEmplacement(ai, aiPos, map, aiComponents)) {
        // std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
        // std::cout << "Escape (after pose the bomb) to X: " << ai.posToEscape.X << ", Y: " << ai.posToEscape.Y << std::endl;

        AStarAlgorithm astar(
            _mapX,
            _mapY,
            std::pair<int, int>(aiPos.X, aiPos.Y),
            std::pair<int, int>(ai.longObjective.X, ai.longObjective.Y),
            [this, &bomberman, &map, &ai, &aiPos](const std::pair<int, int> &pos) ->bool {
                if (posIsHideFromBombs(ai, aiPos, map) && !posIsHideFromBombs(ai, irr::core::vector2di(pos.first, pos.second), map))
                    return (true);
                return (!isAirBlock(map[pos.first][pos.second], bomberman));
        });
        astar.searchPath();
        std::optional<std::pair<int, int>> pos;
        ai.path.clear();
        while ((pos = astar.getNextPos()).has_value()) {
            ai.path.emplace_back(pos.value());
        }

        setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    } else {
        ai.state = AIControllerComponent::NONE;
    }
}

bool AIControllerSystem::posIsHideFromABomb(
    const irr::core::vector2di &aiPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const irr::core::vector2di &bombPos,
    const BombermanComponent &bomberman,
    int bombSize
) const noexcept
{
    if (aiPos.X != bombPos.X && aiPos.Y != bombPos.Y)
        return (true);
    if (aiPos.X == bombPos.X && aiPos.Y == bombPos.Y)
        return (false);
    if (aiPos.X == bombPos.X) {
        int incr = (bombPos.Y < aiPos.Y ? -1 : 1);

        int a = 0;
        for (int tmp = aiPos.Y; tmp != bombPos.Y; tmp += incr, a++) {
            if (layerIsABlock(map[bombPos.X][tmp], bomberman) || a == bombSize)
                return (true);
        }
        return (false);
    } else if (aiPos.Y == bombPos.Y) {
        int incr = (bombPos.X < aiPos.X ? -1 : 1);

        int a = 0;
        for (int tmp = aiPos.X; tmp != bombPos.X; tmp += incr, a++) {
            if (layerIsABlock(map[tmp][bombPos.Y], bomberman) || a == bombSize)
                return (true);
        }
        return (false);
    }
    return (true);
}

int AIControllerSystem::getSizeBomb(const std::vector<std::shared_ptr<Component>> &bombs, const irr::core::vector2di &pos) const
{
    int max = 1;

    for (const std::shared_ptr<Component> &component : bombs) {
        const BombComponent &bomb = *static_cast<BombComponent *>(component.get());
    
        int x = (bomb._pos.X) / 3 + (int)(_mapX / 2);
        int y = (bomb._pos.Z) / 3 + (int)(_mapY / 2);

        if (pos.X == x && pos.Y == y)
            if (bomb.bombSize > max)
                max = bomb.bombSize;
    }
    return (max);
}

bool AIControllerSystem::posIsHideFromBombs(
    const AIControllerComponent &ai,
    const irr::core::vector2di &aiPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map
) const
{
    int iSize = map.size();
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();
    std::vector<std::shared_ptr<Component>> &bombs = _componentManager->getComponentsByType(typeid(BombComponent).hash_code());

    for (int i = 0; i < iSize; i++) {
        int jSize = map[i].size();
        
        for (int j = 0; j < jSize; j++) {
            if (map[i][j] != is::ecs::Entity::BOMB)
                continue;
            int sizeBomb = getSizeBomb(bombs, irr::core::vector2di(i, j));
            if (!posIsHideFromABomb(aiPos, map, irr::core::vector2di(i, j), bomberman, sizeBomb))
                return (false);
        }
    }
    return (true);
}

// * pos : the position of the bomb
bool AIControllerSystem::canHideFromExplosion(
    AIControllerComponent &ai,
    const irr::core::vector2di &pos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map
) const
{
    std::vector<irr::core::vector2di> successors;
    std::list<irr::core::vector2di> closeList;
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    successors.emplace_back(irr::core::vector2di(pos.X + 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y + 1));
    successors.emplace_back(irr::core::vector2di(pos.X - 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y - 1));
    while (successors.size() != 0) {
        irr::core::vector2di newPos = successors[0];

        successors.erase(successors.begin());
        if (std::find_if(closeList.begin(), closeList.end(), [&newPos](const irr::core::vector2di &pos) -> bool {return pos == newPos;}) != closeList.end())
            continue;
        if (!isValid(newPos, map) || !isAirBlock(map[newPos.X][newPos.Y], bomberman))
            continue;
        if (posIsHideFromABomb(newPos, map, pos, bomberman, bomberman.bombRange) && posIsHideFromBombs(ai, newPos, map)) {
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
    const AIControllerComponent &ai,
    const irr::core::vector2di &bombPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const irr::core::vector2di &aiPos,
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();
    int dirX[] = {-bomberman.bombRange, 0, bomberman.bombRange, 0};
    int dirY[] = {0, -bomberman.bombRange, 0, bomberman.bombRange};

    if (bombPosAimForPlayer(ai, bombPos, map, aiComponents))
        return (true);
    for (int i = 0; i < 4; i++) {
        if (dirX[i]) {
            int incr = dirX[i] < 0 ? -1 : 1;

            for (int x = incr; (dirX[i] < 0 ? x >= dirX[i] : x <= dirX[i]); x += incr) {
                if (!isValid(irr::core::vector2di(bombPos.X + x, bombPos.Y), map))
                    break;
                if (map[bombPos.X + x][bombPos.Y] == is::ecs::Entity::Layer::GROUND)
                    break;
                if (map[bombPos.X + x][bombPos.Y] == is::ecs::Entity::Layer::BRKBL_BLK)
                    return (true);
            }
        } else {
            int incr = dirY[i] < 0 ? -1 : 1;

            for (int y = incr; (dirY[i] < 0 ? y >= dirY[i] : y <= dirY[i]); y += incr) {
                if (!isValid(irr::core::vector2di(bombPos.X, bombPos.Y + y), map))
                    break;
                if (map[bombPos.X][bombPos.Y + y] == is::ecs::Entity::Layer::GROUND)
                    break;
                if (map[bombPos.X][bombPos.Y + y] == is::ecs::Entity::Layer::BRKBL_BLK)
                    return (true);
            }
        }
    }
    return (false);
}

bool AIControllerSystem::findBombEmplacement(
    AIControllerComponent &ai,
    const irr::core::vector2di &pos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    std::vector<irr::core::vector2di> successors;
    std::list<irr::core::vector2di> closeList;
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    successors.emplace_back(irr::core::vector2di(pos.X + 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y + 1));
    successors.emplace_back(irr::core::vector2di(pos.X - 1, pos.Y));
    successors.emplace_back(irr::core::vector2di(pos.X, pos.Y - 1));
    while (successors.size() != 0) {
        irr::core::vector2di newPos = successors[0];

        successors.erase(successors.begin());
        if (std::find_if(closeList.begin(), closeList.end(), [&newPos](const irr::core::vector2di &pos) -> bool {return pos == newPos;}) != closeList.end())
            continue;
        if (!isValid(newPos, map) || !isAirBlock(map[newPos.X][newPos.Y], bomberman))
            continue;
        // if he is not in danger and the new pos is in danger
        if (posIsHideFromBombs(ai, pos, map) && !posIsHideFromBombs(ai, newPos, map))
            continue;
        if (bombPosIsUseful(ai, newPos, map, pos, aiComponents) && canHideFromExplosion(ai, newPos, map)) {
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
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<Component>> &aiComponents
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

void AIControllerSystem::putBombState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPosF,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<Component>> &aiComponents
) const
{
    // std::cout << "PUT BOMB STATE" << std::endl;
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    moveAI(ai, aiPosF);
    if (hasReachedObjective(ai, aiPosF)) {
        if (!bombPosIsUseful(ai, ai.longObjective, map, irr::core::vector2di(aiPosF.X, aiPosF.Y), aiComponents)) {
            ai.state = AIControllerComponent::NONE;
            return;
        }
        if (ai.shortObjective == ai.longObjective) {
            ai.getInputManager().setValue("DropBomb", 1);
            ai.bombPos = ai.longObjective;
            ai.state = AIControllerComponent::ESCAPE_EXPLOSION;
            ai.longObjective = ai.posToEscape;
            // std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
            ai.lastShortObjective = ai.shortObjective;
            irr::core::vector2di aiPos(aiPosF.X, aiPosF.Y);

            AStarAlgorithm astar(
                _mapX,
                _mapY,
                std::pair<int, int>(aiPos.X, aiPos.Y),
                std::pair<int, int>(ai.longObjective.X, ai.longObjective.Y),
                [this, &bomberman, &map, &ai, &aiPos](const std::pair<int, int> &pos) -> bool {
                    return (!isAirBlock(map[pos.first][pos.second], bomberman));
            });
            astar.searchPath();
            std::optional<std::pair<int, int>> pos;
            ai.path.clear();
            while ((pos = astar.getNextPos()).has_value()) {
                ai.path.emplace_back(pos.value());
            }
        }
        setNewShortObjective(ai, irr::core::vector2di(aiPosF.X, aiPosF.Y), map);
    }
}


/****************************\
*
* WAITING STATE
*
*****************************/

void AIControllerSystem::waitingState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPosF,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<Component>> &aiComponents
) const
{
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();
    irr::core::vector2di aiPos(aiPosF.X, aiPosF.Y);

    // std::cout << "WAITING STATE" << std::endl;
    if (!posIsHideFromBombs(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map)) {
        // std::cout << "I am not hide" << std::endl;
        if (canHideFromExplosion(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map)) {
            ai.longObjective = ai.posToEscape;
            ai.state = AIControllerComponent::AIState::ESCAPE_EXPLOSION;
            // std::cout << "Hide to position Y: " << ai.longObjective.Y << ", X: " << ai.longObjective.X << std::endl;
            AStarAlgorithm astar(
                _mapX,
                _mapY,
                std::pair<int, int>(aiPos.X, aiPos.Y),
                std::pair<int, int>(ai.longObjective.X, ai.longObjective.Y),
                [this, &bomberman, &map, &ai, &aiPos](const std::pair<int, int> &pos) -> bool {
                    if (posIsHideFromBombs(ai, aiPos, map) && !posIsHideFromBombs(ai, irr::core::vector2di(pos.first, pos.second), map))
                        return (true);
                    return (!isAirBlock(map[pos.first][pos.second], bomberman));
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
    if (bomberman.bombNumber != bomberman.instantBomb)
        ai.state = AIControllerComponent::NONE;
    // if (map[ai.bombPos.X][ai.bombPos.Y] != is::ecs::Entity::Layer::BOMB)
    //     ai.state = AIControllerComponent::NONE;
}


/****************************\
*
* GET POWERUP STATE
*
*****************************/

void AIControllerSystem::getPowerupState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{

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

bool AIControllerSystem::isAirBlock(is::ecs::Entity::Layer layer, const BombermanComponent &bomberman) const noexcept
{
    if (bomberman.wallPass)
        if (layer == is::ecs::Entity::BRKBL_BLK)
            return (true);
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

bool AIControllerSystem::layerIsABlock(const is::ecs::Entity::Layer &layer, const BombermanComponent &bomberman) const noexcept
{
    if (bomberman.wallPass)
        if (layer == is::ecs::Entity::BRKBL_BLK)
            return (false);
    return (layer == is::ecs::Entity::Layer::BRKBL_BLK || layer == is::ecs::Entity::Layer::GROUND || layer == is::ecs::Entity::Layer::FIRE);
}

static bool findPlayer(
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents,
    const irr::core::vector2di &bombPos,
    const is::components::AIControllerComponent &ai,
    int i,
    const std::function<bool(int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos)> &fct
)
{
    return (std::find_if(aiComponents.begin(), aiComponents.end(), [&ai, &i, &bombPos, &fct](const std::shared_ptr<Component> &component) -> bool {
        CharacterControllerComponent &aiComponent = *static_cast<CharacterControllerComponent *>(component.get());
        CharacterControllerComponent &character = *ai.getEntity()->getComponent<CharacterControllerComponent>().value();

        if (character == aiComponent)
            return (false);
        TransformComponent &tr = *static_cast<TransformComponent *>(aiComponent.getEntity()->getComponent<TransformComponent>()->get());
        irr::core::vector2di aiPos;
        
        int mapX = 13, mapY = 15;
        aiPos.X = (tr.position.X + (int)(mapX * 3 / 2)) / 3;
        aiPos.Y = (tr.position.Z + (int)(mapY * 3 / 2)) / 3;

        return (fct(i, aiPos, bombPos));
    }) != aiComponents.end());
}

bool AIControllerSystem::bombPosAimForPlayer(
    const is::components::AIControllerComponent &ai,
    const irr::core::vector2di &bombPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const noexcept
{
    int width = map.size();
    int height = map[bombPos.X].size();
    BombermanComponent &bombermanComponent = *ai.getEntity()->getComponent<BombermanComponent>().value();

    for (int i = bombPos.X; i < width && i - bombPos.X <= bombermanComponent.bombRange; i++) {
        if (layerIsABlock(map[i][bombPos.Y], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (i == aiPos.X && bombPos.Y == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.X; i > 0 && bombPos.X - i <= bombermanComponent.bombRange; i--) {
        if (layerIsABlock(map[i][bombPos.Y], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (i == aiPos.X && bombPos.Y == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.Y; i < height && i - bombPos.Y <= bombermanComponent.bombRange; i++) {
        if (layerIsABlock(map[bombPos.X][i], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (bombPos.X == aiPos.X && i == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.Y; i > 0 && bombPos.Y - i <= bombermanComponent.bombRange; i--) {
        if (layerIsABlock(map[bombPos.X][i], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (bombPos.X == aiPos.X && i == aiPos.Y);
        }))
            return (true);
    }
    return (false);
}
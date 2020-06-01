/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIController
*/

#include "Systems/AIControllerLevel5.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void AIControllerLevel5System::awake()
{
    std::vector<std::shared_ptr<Component>> &aiComponents =
        _componentManager->getComponentsByType(typeid(AIControllerComponent).hash_code());

    for (std::shared_ptr<Component> &component: aiComponents) {
        if (component->getEntity()->isInit())
            continue;
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());

        if (ai.getLevel() != 5)
            continue;

        ai.getInputManager().addValue("MoveHorizontalAxis", 0);
        ai.getInputManager().addValue("MoveVerticalAxis", 0);
        ai.getInputManager().addValue("Jump", 0);
        ai.getInputManager().addValue("DropBomb", 0);
    }

    _mapFunctionState[AIControllerComponent::AIState::NONE] = &AIControllerLevel5System::noneState;
    _mapFunctionState[AIControllerComponent::AIState::ESCAPE_EXPLOSION] = &AIControllerLevel5System::escapeExplosionState;
    _mapFunctionState[AIControllerComponent::AIState::PUT_BOMB] = &AIControllerLevel5System::putBombState;
    _mapFunctionState[AIControllerComponent::AIState::WAITING] = &AIControllerLevel5System::waitingState;
}

void AIControllerLevel5System::start()
{
    std::vector<std::shared_ptr<Component>> &time =
        _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());

    if (!time.size())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<TimeComponent *>(time[0].get()));
}

void AIControllerLevel5System::stop()
{}

void AIControllerLevel5System::onTearDown()
{}

void AIControllerLevel5System::update()
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

        if (ai.getLevel() != 5)
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


/****************************\
*
* NONE STATE
*
*****************************/

void AIControllerLevel5System::noneState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos, 
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<Component>> &aiComponents
) const
{
    ai.lastShortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
    ai.shortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
    setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map, aiComponents);
}

void AIControllerLevel5System::setNewLongObjective(
    AIControllerComponent &ai,
    irr::core::vector2di aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    if (findBombEmplacement(ai, aiPos, map, aiComponents)) {
        AStarAlgorithm astar(
            _mapX,
            _mapY,
            std::pair<int, int>(aiPos.X, aiPos.Y),
            std::pair<int, int>(ai.longObjective.X, ai.longObjective.Y),
            [this, &bomberman, &map, &ai, &aiPos](const std::pair<int, int> &pos) ->bool {
                if (posIsHideFromBombs(ai, aiPos, map) && !posIsHideFromBombs(ai, irr::core::vector2di(pos.first, pos.second), map))
                    return (true);
                return (!AIControllerUtils::isAirBlock(map[pos.first][pos.second], bomberman));
        });
        astar.searchPath();
        std::optional<std::pair<int, int>> pos;
        ai.path.clear();
        while ((pos = astar.getNextPos()).has_value()) {
            ai.path.emplace_back(pos.value());
        }

        AIControllerUtils::setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    } else {
        ai.state = AIControllerComponent::NONE;
    }
}

bool AIControllerLevel5System::posIsHideFromABomb(
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
            if (AIControllerUtils::layerIsABlock(map[bombPos.X][tmp], bomberman) || a == bombSize)
                return (true);
        }
        return (false);
    } else if (aiPos.Y == bombPos.Y) {
        int incr = (bombPos.X < aiPos.X ? -1 : 1);

        int a = 0;
        for (int tmp = aiPos.X; tmp != bombPos.X; tmp += incr, a++) {
            if (AIControllerUtils::layerIsABlock(map[tmp][bombPos.Y], bomberman) || a == bombSize)
                return (true);
        }
        return (false);
    }
    return (true);
}

int AIControllerLevel5System::getSizeBomb(const std::vector<std::shared_ptr<Component>> &bombs, const irr::core::vector2di &pos) const
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

bool AIControllerLevel5System::posIsHideFromBombs(
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
bool AIControllerLevel5System::canHideFromExplosion(
    AIControllerComponent &ai,
    const irr::core::vector2di &pos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map
) const
{
    std::vector<irr::core::vector2di> successors;
    std::vector<irr::core::vector2di> closeList;
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
        if (!AIControllerUtils::isValid(newPos, map) || !AIControllerUtils::isAirBlock(map[newPos.X][newPos.Y], bomberman))
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

bool AIControllerLevel5System::bombPosIsUseful(
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
                if (!AIControllerUtils::isValid(irr::core::vector2di(bombPos.X + x, bombPos.Y), map))
                    break;
                if (map[bombPos.X + x][bombPos.Y] == is::ecs::Entity::Layer::GROUND)
                    break;
                if (map[bombPos.X + x][bombPos.Y] == is::ecs::Entity::Layer::BRKBL_BLK)
                    return (true);
            }
        } else {
            int incr = dirY[i] < 0 ? -1 : 1;

            for (int y = incr; (dirY[i] < 0 ? y >= dirY[i] : y <= dirY[i]); y += incr) {
                if (!AIControllerUtils::isValid(irr::core::vector2di(bombPos.X, bombPos.Y + y), map))
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

bool AIControllerLevel5System::findBombEmplacement(
    AIControllerComponent &ai,
    const irr::core::vector2di &pos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    std::vector<irr::core::vector2di> successors;
    std::vector<irr::core::vector2di> closeList;
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
        if (!AIControllerUtils::isValid(newPos, map) || !AIControllerUtils::isAirBlock(map[newPos.X][newPos.Y], bomberman))
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

void AIControllerLevel5System::escapeExplosionState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<Component>> &aiComponents
) const
{
    // std::cout << "ESCAPE EXPLOSION STATE" << std::endl;
    AIControllerUtils::moveAI(ai, aiPos);
    if (AIControllerUtils::hasReachedObjective(ai, aiPos)) {
        if (ai.shortObjective == ai.longObjective) {
            ai.state = AIControllerComponent::WAITING;
            ai.lastShortObjective = ai.shortObjective;
            return;
        }
        AIControllerUtils::setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    }
}


/****************************\
*
* PUT BOMB STATE
*
*****************************/

void AIControllerLevel5System::putBombState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPosF,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<Component>> &aiComponents
) const
{
    // std::cout << "PUT BOMB STATE" << std::endl;
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    AIControllerUtils::moveAI(ai, aiPosF);
    if (AIControllerUtils::hasReachedObjective(ai, aiPosF)) {
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
                    return (!AIControllerUtils::isAirBlock(map[pos.first][pos.second], bomberman));
            });
            astar.searchPath();
            std::optional<std::pair<int, int>> pos;
            ai.path.clear();
            while ((pos = astar.getNextPos()).has_value()) {
                ai.path.emplace_back(pos.value());
            }
        }
        AIControllerUtils::setNewShortObjective(ai, irr::core::vector2di(aiPosF.X, aiPosF.Y), map);
    }
}


/****************************\
*
* WAITING STATE
*
*****************************/

void AIControllerLevel5System::waitingState(
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
                    return (!AIControllerUtils::isAirBlock(map[pos.first][pos.second], bomberman));
            });
            astar.searchPath();
            std::optional<std::pair<int, int>> pos;
            ai.path.clear();
            while ((pos = astar.getNextPos()).has_value()) {
                ai.path.emplace_back(pos.value());
            }
            AIControllerUtils::setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
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

void AIControllerLevel5System::getPowerupState(
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

bool AIControllerLevel5System::isInDanger(irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const
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

bool AIControllerLevel5System::bombPosAimForPlayer(
    const is::components::AIControllerComponent &ai,
    const irr::core::vector2di &bombPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    int width = map.size();
    int height = map[bombPos.X].size();
    BombermanComponent &bombermanComponent = *ai.getEntity()->getComponent<BombermanComponent>().value();

    for (int i = bombPos.X; i < width && i - bombPos.X <= bombermanComponent.bombRange; i++) {
        if (AIControllerUtils::layerIsABlock(map[i][bombPos.Y], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (i == aiPos.X && bombPos.Y == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.X; i > 0 && bombPos.X - i <= bombermanComponent.bombRange; i--) {
        if (AIControllerUtils::layerIsABlock(map[i][bombPos.Y], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (i == aiPos.X && bombPos.Y == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.Y; i < height && i - bombPos.Y <= bombermanComponent.bombRange; i++) {
        if (AIControllerUtils::layerIsABlock(map[bombPos.X][i], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (bombPos.X == aiPos.X && i == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.Y; i > 0 && bombPos.Y - i <= bombermanComponent.bombRange; i--) {
        if (AIControllerUtils::layerIsABlock(map[bombPos.X][i], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (bombPos.X == aiPos.X && i == aiPos.Y);
        }))
            return (true);
    }
    return (false);
}
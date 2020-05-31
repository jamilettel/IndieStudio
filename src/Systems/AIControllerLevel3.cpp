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
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    ai.lastShortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
    ai.shortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
    if (findBombEmplacement(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map, aiComponents)) {
        AStarAlgorithm astar(
            _mapX,
            _mapY,
            std::pair<int, int>(aiPos.X, aiPos.Y),
            std::pair<int, int>(ai.longObjective.X, ai.longObjective.Y),
            [this, &bomberman, &map, &ai, &aiPos](const std::pair<int, int> &pos) ->bool {
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

bool AIControllerLevel3System::posIsHideFromABomb(
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
            if (AIControllerUtils::layerIsABlock(map[bombPos.X][tmp], bomberman))
                return (true);
        }
        return (false);
    } else if (aiPos.Y == bombPos.Y) {
        int incr = (bombPos.X < aiPos.X ? -1 : 1);

        int a = 0;
        for (int tmp = aiPos.X; tmp != bombPos.X; tmp += incr, a++) {
            if (AIControllerUtils::layerIsABlock(map[tmp][bombPos.Y], bomberman))
                return (true);
        }
        return (false);
    }
    return (true);
}

int AIControllerLevel3System::getSizeBomb(const std::vector<std::shared_ptr<Component>> &bombs, const irr::core::vector2di &pos) const
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

bool AIControllerLevel3System::posIsHideFromBombs(
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

bool AIControllerLevel3System::canHideFromExplosion(
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

bool AIControllerLevel3System::bombPosIsUseful(
    const AIControllerComponent &ai,
    const irr::core::vector2di &bombPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const irr::core::vector2di &aiPos,
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    int dirX[] = {-1, 0, 1, 0};
    int dirY[] = {0, -1, 0, 1};

    if (bombPosAimForPlayer(ai, bombPos, map, aiComponents))
        return (true);
    for (int i = 0; i < 4; i++) {
        if (!AIControllerUtils::isValid(irr::core::vector2di(bombPos.X + dirX[i], bombPos.Y + dirY[i]), map))
            continue;
        if (map[bombPos.X + dirX[i]][bombPos.Y + dirY[i]] == is::ecs::Entity::Layer::BRKBL_BLK)
            return (true);
    }
    return (false);
}

bool AIControllerLevel3System::findBombEmplacement(
    is::components::AIControllerComponent &ai,
    const irr::core::vector2di &aiPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    std::vector<irr::core::vector2di> successors;
    std::vector<irr::core::vector2di> closeList;
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    successors.emplace_back(irr::core::vector2di(aiPos.X + 1, aiPos.Y));
    successors.emplace_back(irr::core::vector2di(aiPos.X, aiPos.Y + 1));
    successors.emplace_back(irr::core::vector2di(aiPos.X - 1, aiPos.Y));
    successors.emplace_back(irr::core::vector2di(aiPos.X, aiPos.Y - 1));
    while (successors.size() != 0) {
        irr::core::vector2di newPos = successors[0];

        successors.erase(successors.begin());
        if (std::find_if(closeList.begin(), closeList.end(), [&newPos](const irr::core::vector2di &pos) -> bool {return pos == newPos;}) != closeList.end())
            continue;
        if (!AIControllerUtils::isValid(newPos, map) || !AIControllerUtils::isAirBlock(map[newPos.X][newPos.Y], bomberman))
            continue;
        // if he is not in danger and the new pos is in danger
        if (posIsHideFromBombs(ai, aiPos, map) && !posIsHideFromBombs(ai, newPos, map))
            continue;
        if (bombPosIsUseful(ai, newPos, map, aiPos, aiComponents) && canHideFromExplosion(ai, newPos, map)) {
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


void AIControllerLevel3System::escapeExplosionState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    if (!ai.waitTime)
        AIControllerUtils::moveAI(ai, aiPos);
    else {
        ai.getInputManager().setValue("DropBomb", 1);
        ai.waitTime = false;
        return;
    }
    if (AIControllerUtils::hasReachedObjective(ai, aiPos)) {
        if (ai.shortObjective == ai.longObjective) {
            ai.state = AIControllerComponent::WAITING;
            ai.lastShortObjective = ai.shortObjective;
            return;
        }
        AIControllerUtils::setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    }
}

void AIControllerLevel3System::putBombState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    AIControllerUtils::moveAI(ai, aiPos);
    if (AIControllerUtils::hasReachedObjective(ai, aiPos)) {
        if (!bombPosIsUseful(ai, ai.longObjective, map, irr::core::vector2di(aiPos.X, aiPos.Y), aiComponents)) {
            ai.state = AIControllerComponent::NONE;
            return;
        }
        if (ai.shortObjective == ai.longObjective) {
            ai.timeBeforeBegin = 0.5f;
            ai.waitTime = true;
            ai.bombPos = ai.longObjective;
            ai.state = AIControllerComponent::ESCAPE_EXPLOSION;
            ai.longObjective = ai.posToEscape;
            ai.lastShortObjective = ai.shortObjective;

            AStarAlgorithm astar(
                _mapX,
                _mapY,
                std::pair<int, int>(aiPos.X, aiPos.Y),
                std::pair<int, int>(ai.longObjective.X, ai.longObjective.Y),
                [this, &bomberman, &map](const std::pair<int, int> &pos) -> bool {
                    return (!AIControllerUtils::isAirBlock(map[pos.first][pos.second], bomberman));
            });
            astar.searchPath();
            std::optional<std::pair<int, int>> pos;
            ai.path.clear();
            while ((pos = astar.getNextPos()).has_value()) {
                ai.path.emplace_back(pos.value());
            }
        }
        AIControllerUtils::setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    }
}

// WAITING STATE
void AIControllerLevel3System::waitingState(
    is::components::AIControllerComponent &ai,
    irr::core::vector2df &aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    BombermanComponent &bomberman = *ai.getEntity()->getComponent<BombermanComponent>().value();

    if (bomberman.instantBomb == 0) {
        ai.state = AIControllerComponent::NONE;
        ai.timeBeforeBegin = 0.5f;
    }
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

bool AIControllerLevel3System::bombPosAimForPlayer(
    const is::components::AIControllerComponent &ai,
    const irr::core::vector2di &bombPos,
    const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
    const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
) const
{
    int width = map.size();
    int height = map[bombPos.X].size();
    BombermanComponent &bombermanComponent = *ai.getEntity()->getComponent<BombermanComponent>().value();

    for (int i = bombPos.X; i < width && i - bombPos.X <= 1; i++) {
        if (AIControllerUtils::layerIsABlock(map[i][bombPos.Y], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (i == aiPos.X && bombPos.Y == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.X; i > 0 && bombPos.X - i <= 1; i--) {
        if (AIControllerUtils::layerIsABlock(map[i][bombPos.Y], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (i == aiPos.X && bombPos.Y == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.Y; i < height && i - bombPos.Y <= 1; i++) {
        if (AIControllerUtils::layerIsABlock(map[bombPos.X][i], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (bombPos.X == aiPos.X && i == aiPos.Y);
        }))
            return (true);
    }
    for (int i = bombPos.Y; i > 0 && bombPos.Y - i <= 1; i--) {
        if (AIControllerUtils::layerIsABlock(map[bombPos.X][i], bombermanComponent))
            break;
        if (findPlayer(aiComponents, bombPos, ai, i, [](int i, const irr::core::vector2di &aiPos, const irr::core::vector2di &bombPos) -> bool {
            return (bombPos.X == aiPos.X && i == aiPos.Y);
        }))
            return (true);
    }
    return (false);
}
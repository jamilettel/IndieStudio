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
    std::cout << "NONE STATE" << std::endl;
    if (ai.firstObjective) {
        ai.lastShortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
        ai.shortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
        ai.firstObjective = false;
    }
    ai.lastMoves.clear();
    setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
}

void AIControllerSystem::setNewLongObjective(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const
{
    ai.last2.clear();
    ai.last.clear();
    if (findBombEmplacement(ai, aiPos, map, aiPos)) {
        std::cout << "FIND EMPLACEMENT FOR BOMB" << std::endl;
        std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
        std::cout << "Escape (after pose the bomb) to X: " << ai.posToEscape.X << ", Y: " << ai.posToEscape.Y << std::endl;
        ai.needObjective = false;
        ai.needLongObjective = false;
    } else {
        std::cout << "CANT FIND EMPLACEMENT FOR BOMB" << std::endl;
        ai.state = AIControllerComponent::NONE;
    }
}

bool AIControllerSystem::canHideFromExplosion(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map, irr::core::vector2di bombPos, irr::core::vector2di lastPos) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};

    for (int i = 0; i < 4; i++) {
        irr::core::vector2di newPos(aiPos.X + dirX[i], aiPos.Y + dirY[i]);

        if (hasAlreadyPass(ai.last2, newPos))
            continue;
        if (newPos.X == lastPos.X && newPos.Y == lastPos.Y)
            continue;
        if (!isAirBlock(map[aiPos.X + dirX[i]][aiPos.Y + dirY[i]]))
            continue;

        if (newPos.X != bombPos.X && newPos.Y != bombPos.Y) {
            ai.posToEscape = newPos;
            return (true);
        }
        ai.last2.emplace_back(newPos);
        if (canHideFromExplosion(ai, newPos, map, bombPos, aiPos))
            return (true);
    }
    return (false);
}

bool AIControllerSystem::bombPosIsUseful(irr::core::vector2di &bombPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};

    // std::cout << "Bomb pos is useful with position X:" << bombPos.X << " and Y:" << bombPos.Y << std::endl << std::flush;
    for (int i = 0; i < 4; i++) {
        irr::core::vector2di newPos(bombPos.X + dirX[i], bombPos.Y + dirY[i]);

        if (map[bombPos.X + dirX[i]][bombPos.Y + dirY[i]] == is::ecs::Entity::Layer::BRKBL_BLK)
            return (true);
    }
    return (false);
}

bool AIControllerSystem::findBombEmplacement(AIControllerComponent &ai, irr::core::vector2di pos, std::vector<std::vector<is::ecs::Entity::Layer>> &map, irr::core::vector2di lastPos) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};

    for (int i = 0; i < 4; i++) {
        irr::core::vector2di newPos(pos.X + dirX[i], pos.Y + dirY[i]);

        if (hasAlreadyPass(ai.last, newPos))
            continue;
        if (newPos.X == lastPos.X && newPos.Y == lastPos.Y)
            continue;
        if (!isAirBlock(map[newPos.X][newPos.Y]))
            continue;
        if (bombPosIsUseful(newPos, map) && canHideFromExplosion(ai, newPos, map, newPos, irr::core::vector2di(0, 0))) {
            ai.state = AIControllerComponent::AIState::PUT_BOMB;
            ai.longObjective = newPos;
            return (true);
        }
        ai.last.emplace_back(newPos);
        if (findBombEmplacement(ai, newPos, map, lastPos))
            return (true);
    }
    return (false);
}


/****************************\
*
* ESCAPE EXPLOSION STATE
*
*****************************/

void AIControllerSystem::escapeExplosionState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    std::cout << "ESCAPE EXPLOSION STATE" << std::endl;
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
    moveAI(ai, aiPos);
}


/****************************\
*
* PUT BOMB STATE
*
*****************************/

void AIControllerSystem::putBombState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    std::cout << "PUT BOMB STATE" << std::endl;

    if (hasReachedObjective(ai, aiPos)) {
        if (ai.shortObjective == ai.longObjective) {
            ai.getInputManager().setValue("DropBomb", 1);
            ai.state = AIControllerComponent::ESCAPE_EXPLOSION;
            ai.longObjective = ai.posToEscape;
            std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
            ai.lastShortObjective = ai.shortObjective;
            return;
        }
        setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
    }
    moveAI(ai, aiPos);
}


/****************************\
*
* WAITING STATE
*
*****************************/

void AIControllerSystem::waitingState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const
{
    std::cout << "WAITING STATE" << std::endl;
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
        ai.needObjective = true;
        ai.needLongObjective = true;
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
    return (!ai.needObjective &&
        aiPos.X - (0.3333f) >= ai.shortObjective.X &&
        aiPos.X - (0.3333f) <= ai.shortObjective.X + 1 &&
        aiPos.X + (0.3333f) >= ai.shortObjective.X &&
        aiPos.X + (0.3333f) <= ai.shortObjective.X + 1 &&
        aiPos.Y - (0.3333f) >= ai.shortObjective.Y &&
        aiPos.Y - (0.3333f) <= ai.shortObjective.Y + 1 &&
        aiPos.Y + (0.3333f) >= ai.shortObjective.Y &&
        aiPos.Y + (0.3333f) <= ai.shortObjective.Y + 1);
}

bool AIControllerSystem::hasAlreadyPass(std::vector<irr::core::vector2di> &moves, irr::core::vector2di &pos) const noexcept
{
    for (auto &e : moves)
        if (e.X == pos.X && e.Y == pos.Y) {
            return (true);
        }
    return (false);
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

    // std::cout << "Enter to setNewShortObjective..." << std::endl;

    // std::cout << "Actual sort objective X :" << ai.shortObjective.X << ", Y:" << ai.shortObjective.Y << std::endl;
    // std::cout << "Actual long objective X :" << ai.longObjective.X << ", Y:" << ai.longObjective.Y << std::endl;
    // std::cout << "Actual last short objective X :" << ai.lastShortObjective.X << ", Y:" << ai.lastShortObjective.Y << std::endl;
    // std::cout << "Actual position X :" << aiPos.X << ", Y:" << aiPos.Y << std::endl;
    int i = aiSearchPath(ai, map, aiPos);
    if (i == 0) {
        ai.state = AIControllerComponent::NONE;
        // std::cout << "C PAS NORMAL CA !!!!!!" << std::endl; 
        ai.needObjective = true;
        ai.needLongObjective = true;
        return;
    }
    ai.lastMoves.push_back(ai.lastShortObjective);
    ai.lastShortObjective = ai.shortObjective;
    ai.shortObjective.X = aiPos.X + dirX[i - 1];
    ai.shortObjective.Y = aiPos.Y + dirY[i - 1];
    // std::cout << "New Short objective X :" << ai.shortObjective.X << ", Y:" << ai.shortObjective.Y << std::endl;
    ai.needObjective = false;
    ai.needLongObjective = false;
}

int AIControllerSystem::aiSearchPath(AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos) const
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};
    int path_finded = 0;
    bool alreadyPass = false;

    for (int i = 0; i < 4; i++) {
        alreadyPass = false;
        // std::cout << "Check for X: " << aiPos.X + dirX[i] << " and Y:" << aiPos.Y + dirY[i] << std::endl;
        for (auto &e : ai.lastMoves)
            if (e.X == aiPos.X + dirX[i] && e.Y == aiPos.Y + dirY[i]) {
                alreadyPass = true;
                // std::cout << "BREAK" << std::endl;
                break;
            }
        // std::cout << "PASS" << std::endl;
        if (alreadyPass) {
            // std::cout << "ALREADY PASS" << std::endl;
            continue;
        }
        if (aiPos.X + dirX[i] == ai.lastShortObjective.X && aiPos.Y + dirY[i] == ai.lastShortObjective.Y) {
            // std::cout << "Same as last short objective" << std::endl;
            continue;
        }
        if (isAirBlock(map[aiPos.X + dirX[i]][aiPos.Y + dirY[i]])) {
            if (aiSearchPathRecursive(ai, map, aiPos, irr::core::vector2di(dirX[i], dirY[i]))) {
                path_finded = i + 1;
                break;
            }
        }
    }
    return (path_finded);
}

bool AIControllerSystem::aiSearchPathRecursive(AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos, irr::core::vector2di dir) const
{
    irr::core::vector2di newAiPos = irr::core::vector2di(aiPos.X + dir.X, aiPos.Y + dir.Y);
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};
    bool alreadyPass = false;

    if (ai.longObjective == newAiPos) {
        return (true);
    }
    for (int i = 0; i < 4; i++) {
        alreadyPass = false;
        for (auto &e : ai.lastMoves)
            if (e.X == aiPos.X + dirX[i] && e.Y == aiPos.Y + dirY[i]) {
                alreadyPass = true;
                break;
            }
        if (alreadyPass)
            continue;
        if (dir.X == -dirX[i] && dir.Y == -dirY[i])
            continue;
        map[aiPos.X][aiPos.Y] = is::ecs::Entity::Layer::GROUND;
        if (!isAirBlock(map[newAiPos.X + dirX[i]][newAiPos.Y + dirY[i]]))
            continue;
        if (aiSearchPathRecursive(ai, map, newAiPos, irr::core::vector2di(dirX[i], dirY[i])))
            return (true);
    }
    return (false);
}


bool AIControllerSystem::isAirBlock(is::ecs::Entity::Layer layer) const
{
    return (layer == is::ecs::Entity::Layer::DEFAULT ||
        layer == is::ecs::Entity::Layer::PLAYER ||
        layer == is::ecs::Entity::Layer::POWERUP);
}

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
        // std::cout << "Entity with position X:" << (tr.position.X) / 3 + (int)(mapX / 2) << " and Y:" << (tr.position.Z) / 3 + (int)(mapY / 2) << std::endl << std::flush;
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

        //setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
        if (ai.firstObjective || ai.needObjective) {
            if (ai.firstObjective) {
                ai.lastShortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
                ai.shortObjective = irr::core::vector2di(aiPos.X, aiPos.Y);
                ai.firstObjective = false;
            }
            // if (ai.firstObjective) {
            //     ai.lastShortObjective.X = aiPos.X;
            //     ai.lastShortObjective.Y = aiPos.Y;
            //     ai.shortObjective.X = aiPos.X;
            //     ai.shortObjective.Y = aiPos.Y + (aiPos.Y > 6 ? -1 : 1);
            //     ai.longObjective.X = (int)(mapX / 2);
            //     ai.longObjective.Y = (int)(mapY / 2);
            //     ai.firstObjective = false;
            //     ai.needObjective = false;
            // }
            if (!ai.needShortObjective) {
                ai.lastMoves.clear();
                setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
            }
            setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
            // if (ai.shortObjective.X == ai.longObjective.X && ai.shortObjective.Y ==  ai.longObjective.Y) {
            //     ai.lastMoves.clear();
            //     setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
            // }
            //else {
                // setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
                // std::cout << "Short x : " << ai.shortObjective.X << ", Y : " << ai.shortObjective.Y << std::endl;
                // std::cout << "last Short x : " << ai.lastShortObjective.X << ", Y : " << ai.lastShortObjective.Y << std::endl;
            //}
        }
        // std::cout << "dckdjkl" << std::endl;
        // if (map[ai.shortObjective.X][ai.shortObjective.Y] == is::ecs::Entity::Layer::BRKBL_BLK) {
        //     ai.getInputManager().setValue("DropBomb", 1);
        //     std::cout << "Short x : " << ai.lastShortObjective.X - ai.shortObjective.X << ", Y : " << ai.lastShortObjective.Y - ai.shortObjective.Y << std::endl;
        //     irr::core::vector2di a = ai.lastShortObjective - ai.shortObjective;
        //     ai.shortObjective += a;
        //     if (ai.lastShortObjective == ai.shortObjective) {
        //         if (ai.shortObjective.X != 1 && ai.shortObjective.Y != 1 &&
        //         ai.shortObjective.X != 13 && ai.shortObjective.Y != 11)
        //             ai.shortObjective += a;
        //     }
        //     std::cout << "Short x : " << ai.shortObjective.X << ", Y : " << ai.shortObjective.Y << std::endl;
        //     std::cout << "Short x : " << ai.lastShortObjective.X << ", Y : " << ai.lastShortObjective.Y << std::endl;
        //     ai.needObjective = false;
        //     std::cout << "coucou" << std::endl;
        // }
        //std::cout << "Short x : " << ai.shortObjective.X << ", Y : " << ai.shortObjective.Y << std::endl;
        //std::cout << "Last short x : " << ai.lastShortObjective.X << ", Y : " << ai.lastShortObjective.Y << std::endl;

        if (hasReachedObjective(ai, aiPos)) {
            ai.needObjective = true;
            if (ai.shortObjective == ai.longObjective) {
                if (ai.state == AIControllerComponent::PUT_BOMB) {
                    ai.getInputManager().setValue("DropBomb", 1);
                    ai.state = AIControllerComponent::ESCAPE_EXPLOSION;
                } else if (ai.state == AIControllerComponent::ESCAPE_EXPLOSION) {
                    ai.state = AIControllerComponent::NONE;
                    std::cout << "NONE" << std::endl;
                    ai.timeBeforeBegin = 3.5f;
                    ai.lastShortObjective = ai.shortObjective;
                    ai.getInputManager().setValue("MoveVerticalAxis", 0);
                    ai.getInputManager().setValue("MoveHorizontalAxis", 0);
                    ai.needShortObjective = false;
                }
            } else {
                std::cout << "ARRIVEEE SHORT" << std::endl;
                ai.needShortObjective = true;
            }
        }
        moveAI(ai, aiPos);
        // if (!ai.needObjective &&
        // aiPos.X - (0.3333f) >= ai.shortObjective.X &&
        // aiPos.X - (0.3333f) <= ai.shortObjective.X + 1 &&
        // aiPos.X + (0.3333f) >= ai.shortObjective.X &&
        // aiPos.X + (0.3333f) <= ai.shortObjective.X + 1 &&
        // aiPos.Y - (0.3333f) >= ai.shortObjective.Y &&
        // aiPos.Y - (0.3333f) <= ai.shortObjective.Y + 1 &&
        // aiPos.Y + (0.3333f) >= ai.shortObjective.Y &&
        // aiPos.Y + (0.3333f) <= ai.shortObjective.Y + 1) {
        //     ai.needObjective = true;
        //     ai.isEscaping = false;
        //     std::cout << "JJJJJJJJJJJJJJ" << std::endl;
        // }
        // if (ai.lastShortObjective == ai.shortObjective) {
        //     ai.needObjective = true;
        //     ai.isEscaping = false;
        // }

    }
}

void AIControllerSystem::moveAI(AIControllerComponent &ai, irr::core::vector2df &aiPos) const
{
    if (ai.state == AIControllerComponent::WAITING || ai.state == AIControllerComponent::NONE) {
        // ai.getInputManager().setValue("MoveVerticalAxis", 0);
        std::cout << "STOP" << std::endl;
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

bool hasAlreadyPass(std::vector<irr::core::vector2di> &moves, irr::core::vector2di &pos)
{
    for (auto &e : moves)
        if (e.X == pos.X && e.Y == pos.Y) {
            return (true);
        }
    return (false);
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

void AIControllerSystem::setNewLongObjective(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const
{
    if (ai.state == AIControllerComponent::ESCAPE_EXPLOSION) {
        ai.longObjective = ai.posToEscape;
        std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
        ai.lastMoves.clear();
        ai.needObjective = false;
        ai.needShortObjective = true;
        ai.lastShortObjective = ai.shortObjective;
    } else if (ai.state == AIControllerComponent::NONE) {
        ai.last2.clear();
        ai.last.clear();
        if (findBombEmplacement(ai, aiPos, map, aiPos)) {
            std::cout << "FIND EMPLACEMENT FOR BOMB" << std::endl;
            std::cout << "New long objective X: " << ai.longObjective.X << ", Y: " << ai.longObjective.Y << std::endl;
            std::cout << "Escape (after pose the bomb) to X: " << ai.posToEscape.X << ", Y: " << ai.posToEscape.Y << std::endl;
            ai.needObjective = false;
            ai.needShortObjective = true;
        } else {
            std::cout << "CANT FIND EMPLACEMENT FOR BOMB" << std::endl;
            ai.state = AIControllerComponent::WAITING;
        }
    }


    // irr::core::vector2di bomberPos(-1);

    // if (ai.isEscaping)
    //     return;
    // for (int i = 0; i < map.size(); i++) {
    //     for (int a = 0; a < map[i].size(); a++) {
    //         if (map[i][a] != is::ecs::Entity::Layer::BOMB) {
    //             continue;
    //         }
    //         if (i == aiPos.X || a == aiPos.Y) {
    //             bomberPos.X = i;
    //             bomberPos.Y = a;
    //             break;
    //         }
    //     }
    // }
    // if (bomberPos.X == -1)
    //     return;
    // std::cout << "JE SUIS UN PD ET EN + Y A UNE BOMBE QUI M'AGRESSE" << std::endl;
    // ai.lastShortObjective = aiPos;

    // char dirX[] = {-1, 0, 1, 0};
    // char dirY[] = {0, -1, 0, 1};
    // float longestDis = 0;

    // ai.needObjective = false;
    // if (bomberPos.X == aiPos.X) {
    //     //ai.shortObjective.Y = aiPos.Y;
    //     if (bomberPos.Y > aiPos.Y)
    //         ai.shortObjective.X++;
    //     else
    //         ai.shortObjective.X--;
    // } else if (bomberPos.Y == aiPos.Y) {
    //     //ai.shortObjective.X = aiPos.X;
    //     if (bomberPos.X > aiPos.X)
    //         ai.shortObjective.Y++;
    //     else
    //         ai.shortObjective.Y--;
    // }
    // std::cout << "Short x : " << ai.shortObjective.X << ", Y : " << ai.shortObjective.Y << std::endl;
    // ai.isEscaping = true;

    // // for (int i = 0; i < 4; i++) {
    // //     if (isAirBlock(map[aiPos.X + dirX[i]][aiPos.Y + dirY[i]])) {
    // //         std::sqrt(std::pow())
    // //     }
    // // }
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
        ai.state = AIControllerComponent::WAITING;
        // std::cout << "C PAS NORMAL CA !!!!!!" << std::endl; 
        return;
    }
    ai.lastMoves.push_back(ai.lastShortObjective);
    ai.lastShortObjective = ai.shortObjective;
    ai.shortObjective.X = aiPos.X + dirX[i - 1];
    ai.shortObjective.Y = aiPos.Y + dirY[i - 1];
    // std::cout << "New Short objective X :" << ai.shortObjective.X << ", Y:" << ai.shortObjective.Y << std::endl;
    ai.needObjective = false;
    ai.needShortObjective = false;
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

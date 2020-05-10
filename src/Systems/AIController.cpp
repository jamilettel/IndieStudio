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

bool cmpf(float A, float B, float epsilon = 0.005f)
{
    return (fabs(A - B) < epsilon);
}

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

        //setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
        if (ai.firstObjective || ai.needObjective) {
            if (ai.firstObjective) {
                ai.lastShortObjective.X = aiPos.X;
                ai.lastShortObjective.Y = aiPos.Y;
                ai.shortObjective.X = aiPos.X;
                ai.shortObjective.Y = aiPos.Y + (aiPos.Y > 6 ? -1 : 1);
                ai.longObjective.X = (int)(mapX / 2);
                ai.longObjective.Y = (int)(mapY / 2);
                ai.firstObjective = false;
                ai.needObjective = false;
            }
            // if (ai.shortObjective.X == ai.longObjective.X && ai.shortObjective.Y ==  ai.longObjective.Y) {
            //     ai.lastMoves.clear();
            //     setNewLongObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
            // }
            //else {
                setNewShortObjective(ai, irr::core::vector2di(aiPos.X, aiPos.Y), map);
                std::cout << "Short x : " << ai.shortObjective.X << ", Y : " << ai.shortObjective.Y << std::endl;
                std::cout << "last Short x : " << ai.lastShortObjective.X << ", Y : " << ai.lastShortObjective.Y << std::endl;
            //}
        }
        std::cout << "dckdjkl" << std::endl;
        if (map[ai.shortObjective.X][ai.shortObjective.Y] == is::ecs::Entity::Layer::BRKBL_BLK) {
            ai.getInputManager().setValue("DropBomb", 1);
            std::cout << "Short x : " << ai.lastShortObjective.X - ai.shortObjective.X << ", Y : " << ai.lastShortObjective.Y - ai.shortObjective.Y << std::endl;
            irr::core::vector2di a = ai.lastShortObjective - ai.shortObjective;
            ai.shortObjective += a;
            if (ai.lastShortObjective == ai.shortObjective) {
                if (ai.shortObjective.X != 1 && ai.shortObjective.Y != 1 &&
                ai.shortObjective.X != 13 && ai.shortObjective.Y != 11)
                    ai.shortObjective += a;
            }
            std::cout << "Short x : " << ai.shortObjective.X << ", Y : " << ai.shortObjective.Y << std::endl;
            std::cout << "Short x : " << ai.lastShortObjective.X << ", Y : " << ai.lastShortObjective.Y << std::endl;
            ai.needObjective = false;
            std::cout << "coucou" << std::endl;
        }
        //std::cout << "Short x : " << ai.shortObjective.X << ", Y : " << ai.shortObjective.Y << std::endl;
        //std::cout << "Last short x : " << ai.lastShortObjective.X << ", Y : " << ai.lastShortObjective.Y << std::endl;

        if (ai.lastShortObjective.Y > ai.shortObjective.Y)
            ai.getInputManager().setValue("MoveHorizontalAxis", -1);
        else if (ai.lastShortObjective.Y < ai.shortObjective.Y)
            ai.getInputManager().setValue("MoveHorizontalAxis", 1);
        else if (ai.lastShortObjective.X > ai.shortObjective.X)
            ai.getInputManager().setValue("MoveVerticalAxis", -1);
        else if (ai.lastShortObjective.X < ai.shortObjective.X)
            ai.getInputManager().setValue("MoveVerticalAxis", 1);
        if (!ai.needObjective &&
        aiPos.X - (0.3333f) >= ai.shortObjective.X &&
        aiPos.X - (0.3333f) <= ai.shortObjective.X + 1 &&
        aiPos.X + (0.3333f) >= ai.shortObjective.X &&
        aiPos.X + (0.3333f) <= ai.shortObjective.X + 1 &&
        aiPos.Y - (0.3333f) >= ai.shortObjective.Y &&
        aiPos.Y - (0.3333f) <= ai.shortObjective.Y + 1 &&
        aiPos.Y + (0.3333f) >= ai.shortObjective.Y &&
        aiPos.Y + (0.3333f) <= ai.shortObjective.Y + 1) {
            ai.needObjective = true;
            ai.isEscaping = false;
            std::cout << "JJJJJJJJJJJJJJ" << std::endl;
        }
        if (ai.lastShortObjective == ai.shortObjective) {
            ai.needObjective = true;
            ai.isEscaping = false;
        }

    }
}

void AIControllerSystem::setNewLongObjective(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map)
{
    irr::core::vector2di bomberPos(-1);

    if (ai.isEscaping)
        return;
    for (int i = 0; i < map.size(); i++) {
        for (int a = 0; a < map[i].size(); a++) {
            if (map[i][a] != is::ecs::Entity::Layer::BOMB) {
                continue;
            }
            if (i == aiPos.X || a == aiPos.Y) {
                bomberPos.X = i;
                bomberPos.Y = a;
                break;
            }
        }
    }
    if (bomberPos.X == -1)
        return;
    std::cout << "JE SUIS UN PD ET EN + Y A UNE BOMBE QUI M'AGRESSE" << std::endl;
    ai.lastShortObjective = aiPos;

    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};
    float longestDis = 0;

    ai.needObjective = false;
    if (bomberPos.X == aiPos.X) {
        //ai.shortObjective.Y = aiPos.Y;
        if (bomberPos.Y > aiPos.Y)
            ai.shortObjective.X++;
        else
            ai.shortObjective.X--;
    } else if (bomberPos.Y == aiPos.Y) {
        //ai.shortObjective.X = aiPos.X;
        if (bomberPos.X > aiPos.X)
            ai.shortObjective.Y++;
        else
            ai.shortObjective.Y--;
    }
    std::cout << "Short x : " << ai.shortObjective.X << ", Y : " << ai.shortObjective.Y << std::endl;
    ai.isEscaping = true;

    // for (int i = 0; i < 4; i++) {
    //     if (isAirBlock(map[aiPos.X + dirX[i]][aiPos.Y + dirY[i]])) {
    //         std::sqrt(std::pow())
    //     }
    // }
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

void AIControllerSystem::setNewShortObjective(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map)
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};

    if (ai.needObjective) {
        int i = aiSearchPath(ai, map, aiPos);
        if (i == 0) {
            //ai.getInputManager().setValue("DropBomb", 1);
            ai.lastMoves.clear();
            // setNewLongObjective(ai, aiPos, map);
            std::cout << ai.longObjective.X << " - " << ai.longObjective.Y << std::endl;
            return;
        }
        ai.lastMoves.push_back(ai.lastShortObjective);
        ai.lastShortObjective = ai.shortObjective;
        ai.shortObjective.X = aiPos.X + dirX[i - 1];
        ai.shortObjective.Y = aiPos.Y + dirY[i - 1];
        ai.needObjective = false;
    }
}

int AIControllerSystem::aiSearchPath(AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos)
{
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};
    int path_finded = 0;
    bool alreadyPass = false;

    for (int i = 0; i < 4; i++) {
        for (auto &e : ai.lastMoves)
            if (e.X == aiPos.X + dirX[i] && e.Y == aiPos.Y + dirY[i]) {
                alreadyPass = true;
                break;
            }
        if (alreadyPass)
            continue;
        if (aiPos.X + dirX[i] == ai.lastShortObjective.X && aiPos.Y + dirY[i] == ai.lastShortObjective.Y)
            continue;
        if (isAirBlock(map[aiPos.X + dirX[i]][aiPos.Y + dirY[i]])) {
            if (aiSearchPathRecursive(ai, map, aiPos, irr::core::vector2di(dirX[i], dirY[i]))) {
                path_finded = i + 1;
                break;
            }
        }
    }
    return (path_finded);
}

bool AIControllerSystem::aiSearchPathRecursive(AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos, irr::core::vector2di dir)
{
    irr::core::vector2di newAiPos = irr::core::vector2di(aiPos.X + dir.X, aiPos.Y + dir.Y);
    char dirX[] = {-1, 0, 1, 0};
    char dirY[] = {0, -1, 0, 1};
    bool alreadyPass = false;

    if (ai.longObjective == newAiPos) {
        return (true);
    }
    for (int i = 0; i < 4; i++) {
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


bool AIControllerSystem::isAirBlock(is::ecs::Entity::Layer layer)
{
    return (layer == is::ecs::Entity::Layer::DEFAULT ||
        layer == is::ecs::Entity::Layer::PLAYER ||
        layer == is::ecs::Entity::Layer::POWERUP ||
        layer == is::ecs::Entity::Layer::BRKBL_BLK);
}

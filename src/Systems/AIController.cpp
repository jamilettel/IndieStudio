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
        map[(tr.position.X) / 3 + (int)(mapX / 2)][(tr.position.Z) / 3 + (int)(mapY / 2)] = tr.getEntity()->layer;
    }

    for (std::shared_ptr<Component> &component: aiComponents) {
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());
        ai.timeBeforeBegin -= _time->get().getCurrentIntervalSeconds();
        if (ai.timeBeforeBegin > 0)
            continue;
        TransformComponent &tr = *static_cast<TransformComponent *>(ai.getEntity()->getComponent<TransformComponent>()->get());
        irr::core::vector2di aiPos;
        aiPos.X = ((int)(tr.position.X) + (tr.position.X < 0 ? 1 : -1)) + (int)(mapX * 3 / 2);
        aiPos.Y = ((int)(tr.position.Z) + (tr.position.Z < 0 ? 1 : -1)) + (int)(mapY * 3 / 2);
        if (ai.firstObjective || ai.needObjective) {
            if (ai.firstObjective) {
                ai.lastShortObjective.X = aiPos.X;
                ai.lastShortObjective.Y = aiPos.Y;
                ai.shortObjective.X = 9 * 3 + 1;
                ai.shortObjective.Y = 11 * 3 + 1;
                ai.longObjective.X = 3 * 3 + 1;
                ai.longObjective.Y = 3 * 3 + 1;
                ai.firstObjective = false;
                ai.needObjective = false;
            }
            else
                setNewObjective(ai, aiPos, map);
        }

        ai.getInputManager().setValue("MoveHorizontalAxis", 0);
        ai.getInputManager().setValue("MoveVerticalAxis", 0);
        if (aiPos.Y > ai.shortObjective.Y)
            ai.getInputManager().setValue("MoveHorizontalAxis", -1);
        else if (aiPos.Y < ai.shortObjective.Y)
            ai.getInputManager().setValue("MoveHorizontalAxis", 1);
        if (aiPos.X > ai.shortObjective.X)
            ai.getInputManager().setValue("MoveVerticalAxis", -1);
        else if (aiPos.X < ai.shortObjective.X)
            ai.getInputManager().setValue("MoveVerticalAxis", 1);
        std::cout << aiPos.X << " -  " << aiPos.Y << std::endl;
        std::cout << "sss" << ai.shortObjective.X << " -  " << ai.shortObjective.Y << std::endl;
        
        if (!ai.needObjective && aiPos.X == ai.shortObjective.X && aiPos.Y == ai.shortObjective.Y) {
            ai.needObjective = true;
            std::cout << "js suis pd" << std::endl;
        }
    }
}

void AIControllerSystem::setNewObjective(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map)
{
    char dirX[] = {-3, 0, 3, 0};
    char dirY[] = {0, -3, 0, 3};

    if (!aiPos.X)
        aiPos.X++;
    if (!aiPos.Y)
        aiPos.Y++;
    if (ai.needObjective) {
        int i = aiSearchPath(ai, map, aiPos);
        if (i == 0) {
            ai.getInputManager().setValue("DropBomb", 1);
            return;
        }
        ai.lastShortObjective = ai.shortObjective;
        ai.shortObjective.X = aiPos.X + dirX[i - 1];
        ai.shortObjective.Y = aiPos.Y + dirY[i - 1];
        ai.needObjective = false;
    }
}

int AIControllerSystem::aiSearchPath(AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos)
{
    char dirX[] = {-3, 0, 3, 0};
    char dirY[] = {0, -3, 0, 3};
    int path_finded = 0;

    for (int i = 0; i < 4; i++) {
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
    char dirX[] = {-3, 0, 3, 0};
    char dirY[] = {0, -3, 0, 3};

    if (ai.longObjective.X == newAiPos.X && ai.longObjective.Y == newAiPos.Y) {
        return (true);
    }
    for (int i = 0; i < 4; i++) {
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
        layer == is::ecs::Entity::Layer::POWERUP);
}

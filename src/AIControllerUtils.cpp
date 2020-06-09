/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIControllerUtils
*/

#include "AIControllerUtils.hpp"

using namespace is;

bool AIControllerUtils::isAirBlock(is::ecs::Entity::Layer layer, const BombermanComponent &bomberman, bool enableWallPass) noexcept
{
    if (bomberman.wallPass && enableWallPass)
        if (layer == is::ecs::Entity::BRKBL_BLK)
            return (true);
    return (layer == is::ecs::Entity::Layer::DEFAULT ||
        layer == is::ecs::Entity::Layer::PLAYER ||
        layer == is::ecs::Entity::Layer::POWERUP); 
}

bool AIControllerUtils::isValid(const irr::core::vector2di &pos, const std::vector<std::vector<is::ecs::Entity::Layer>> &map) noexcept
{
    if (map.size() == 0)
        return (false);
    return (pos.X >= 0 && pos.X < static_cast<int>(map.size()) && pos.Y >= 0 && pos.Y < static_cast<int>(map[0].size()));
}

bool AIControllerUtils::layerIsABlock(const is::ecs::Entity::Layer &layer, const BombermanComponent &bomberman, bool enableWallPass) noexcept
{
    if (bomberman.wallPass && enableWallPass)
        if (layer == is::ecs::Entity::BRKBL_BLK)
            return (false);
    return (layer == is::ecs::Entity::Layer::BRKBL_BLK || layer == is::ecs::Entity::Layer::GROUND || layer == is::ecs::Entity::Layer::FIRE); 
}

void AIControllerUtils::setNewShortObjective(
    is::components::AIControllerComponent &ai,
    irr::core::vector2di aiPos,
    std::vector<std::vector<is::ecs::Entity::Layer>> &map
)
{
    if (!ai.path.size())
        return;
    ai.lastShortObjective = ai.shortObjective;
    ai.shortObjective.X = ai.path[0].first;
    ai.shortObjective.Y = ai.path[0].second;
    ai.path.erase(ai.path.begin());
}

bool AIControllerUtils::hasReachedObjective(AIControllerComponent &ai, irr::core::vector2df &aiPos) noexcept
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

void AIControllerUtils::moveAI(AIControllerComponent &ai, irr::core::vector2df &aiPos)
{
    if (ai.lastShortObjective.Y > ai.shortObjective.Y)
        ai.getInputManager().setValue("MoveHorizontalAxis", -1);
    else if (ai.lastShortObjective.Y < ai.shortObjective.Y)
        ai.getInputManager().setValue("MoveHorizontalAxis", 1);
    else if (ai.lastShortObjective.X > ai.shortObjective.X)
        ai.getInputManager().setValue("MoveVerticalAxis", -1);
    else if (ai.lastShortObjective.X < ai.shortObjective.X)
        ai.getInputManager().setValue("MoveVerticalAxis", 1);
}
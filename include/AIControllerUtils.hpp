/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIControllerUtils
*/

#ifndef AICONTROLLERUTILS_HPP_
#define AICONTROLLERUTILS_HPP_

#include "ECS/Component.hpp"
#include "Components/Bomberman.hpp"
#include "Components/AIController.hpp"

#include "ECS/Entity.hpp"

using namespace is::components;
using namespace is::ecs;

namespace is
{
    class AIControllerUtils {
        public:

            static bool isAirBlock(is::ecs::Entity::Layer, const BombermanComponent &bomberman, bool enableWallPass = false) noexcept;
            static bool isValid(const irr::core::vector2di &pos, const std::vector<std::vector<is::ecs::Entity::Layer>> &map) noexcept;
            static bool layerIsABlock(const is::ecs::Entity::Layer &layer, const BombermanComponent &bomberman, bool enableWallPass = false) noexcept;
            static void setNewShortObjective(
                is::components::AIControllerComponent &ai,
                irr::core::vector2di aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map
            );
            static bool hasReachedObjective(AIControllerComponent &ai, irr::core::vector2df &aiPos) noexcept;
            static void moveAI(AIControllerComponent &ai, irr::core::vector2df &aiPos);
            static void setSuccessors(const irr::core::vector2di &pos, std::vector<irr::core::vector2di> &successors);
    };
} // namespace is



#endif /* !AICONTROLLERUTILS_HPP_ */

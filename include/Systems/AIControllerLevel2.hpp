/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIControllerLevel2
*/

#ifndef AICONTROLLERLEVEL2_HPP_
#define AICONTROLLERLEVEL2_HPP_

#include "AIControllerUtils.hpp"

#include "ECS/ASystem.hpp"

#include "Components/AIController.hpp"
#include "Components/Time.hpp"
#include "Components/Transform.hpp"
#include "Components/CharacterController.hpp"

#include "AStarAlgorithm.hpp"

using namespace is::components;
using namespace is::ecs;

namespace is::systems
{
    class AIControllerLevel2System : public is::ecs::ASystem {
        public:
            AIControllerLevel2System() = default;
            ~AIControllerLevel2System() = default;

            AIControllerLevel2System(const AIControllerLevel2System &) = default;
            AIControllerLevel2System &operator=(const AIControllerLevel2System &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
            // * NONE STATE
            void noneState(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
            ) const;
            bool findBombEmplacement(
                is::components::AIControllerComponent &ai,
                const irr::core::vector2di &aiPos,
                const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
            ) const;
            bool bombPosIsUseful(
                const AIControllerComponent &ai,
                const irr::core::vector2di &bombPos,
                const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                const irr::core::vector2di &aiPos,
                const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
            ) const;
            bool canHideFromExplosion(
                AIControllerComponent &ai,
                const irr::core::vector2di &pos,
                const std::vector<std::vector<is::ecs::Entity::Layer>> &map
            ) const;
            bool posIsHideFromBomb(
                const AIControllerComponent &ai,
                const irr::core::vector2di &aiPos,
                const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                const irr::core::vector2di &bombPos
            ) const;

            void escapeExplosionState(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
            ) const;

            void putBombState(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
            ) const;

            // WAITING STATE
            void waitingState(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
            ) const;

            // GET POWERUP STATE
            void getPowerupState(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
            ) const;

            bool bombPosAimForPlayer(
                const is::components::AIControllerComponent &ai,
                const irr::core::vector2di &bombPos,
                const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
            ) const;

        private:

            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

            using state_function_t = void (AIControllerLevel2System::*)(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents) const;
            std::map<AIControllerComponent::AIState, state_function_t> _mapFunctionState;

            int _mapX = 23;
            int _mapY = 25;
    };

}

#endif /* !AICONTROLLERLEVEL2_HPP_ */
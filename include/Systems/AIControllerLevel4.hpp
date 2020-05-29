/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIControllerLevel4
*/

#ifndef AICONTROLLERLEVEL4_HPP_
#define AICONTROLLERLEVEL4_HPP_

#include "AIControllerUtils.hpp"

#include "ECS/ASystem.hpp"

#include "Components/AIController.hpp"
#include "Components/Time.hpp"
#include "Components/Transform.hpp"
#include "Components/CharacterController.hpp"

using namespace is::components;
using namespace is::ecs;

namespace is::systems
{
    class AIControllerLevel4System : public is::ecs::ASystem {
        public:
            AIControllerLevel4System() = default;
            ~AIControllerLevel4System() = default;

            AIControllerLevel4System(const AIControllerLevel4System &) = default;
            AIControllerLevel4System &operator=(const AIControllerLevel4System &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
            void noneState(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
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

        private:

            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

            using state_function_t = void (AIControllerLevel4System::*)(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents) const;
            std::map<AIControllerComponent::AIState, state_function_t> _mapFunctionState;

            int _mapX = 43;
            int _mapY = 45;
    };

}

#endif /* !AICONTROLLERLEVEL4_HPP_ */
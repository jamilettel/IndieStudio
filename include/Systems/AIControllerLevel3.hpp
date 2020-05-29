/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIControllerLevel3
*/

#ifndef AICONTROLLERLEVEL3_HPP_
#define AICONTROLLERLEVEL3_HPP_

#include "ECS/ASystem.hpp"

#include "Components/AIController.hpp"
#include "Components/Time.hpp"

using namespace is::components;
using namespace is::ecs;

namespace is::systems
{
    class AIControllerLevel3System : public is::ecs::ASystem {
        public:
            AIControllerLevel3System() = default;
            ~AIControllerLevel3System() = default;

            AIControllerLevel3System(const AIControllerLevel3System &) = default;
            AIControllerLevel3System &operator=(const AIControllerLevel3System &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:

            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

            using state_function_t = void (AIControllerLevel3System::*)(
                is::components::AIControllerComponent &ai,
                irr::core::vector2df &aiPos,
                std::vector<std::vector<is::ecs::Entity::Layer>> &map,
                std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents) const;
            std::map<AIControllerComponent::AIState, state_function_t> _mapFunctionState;

            int _mapX = 33;
            int _mapY = 35;
    };

}

#endif /* !AICONTROLLERLEVEL3_HPP_ */
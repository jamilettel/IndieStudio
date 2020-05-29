/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIControllerLevel2
*/

#ifndef AICONTROLLERLEVEL2_HPP_
#define AICONTROLLERLEVEL2_HPP_

#include "ECS/ASystem.hpp"

#include "Components/AIController.hpp"
#include "Components/Time.hpp"

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
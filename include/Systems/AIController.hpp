/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIController
*/

#ifndef AIControllerSYSTEM_HPP_
#define AIControllerSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/AIController.hpp"
#include "Components/Window.hpp"
#include "Components/Movement.hpp"
#include "Components/Transform.hpp"
#include "Components/Time.hpp"
#include <vector>

#include <cmath>

using namespace is::components;

namespace is::systems {

    class AIControllerSystem: public is::ecs::ASystem {
    public:
        AIControllerSystem() = default;
        ~AIControllerSystem() = default;

        AIControllerSystem(const AIControllerSystem &) = default;
        AIControllerSystem &operator=(const AIControllerSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

    private:
        // NONE STATE
        void noneState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;
        void setNewLongObjective(is::components::AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const;
        bool findBombEmplacement(AIControllerComponent &ai, irr::core::vector2di newPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map, irr::core::vector2di lastPos) const;
        bool canHideFromExplosion(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map, irr::core::vector2di pos, irr::core::vector2di lastPos) const;
        bool bombPosIsUseful(irr::core::vector2di &bombPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;

        // ESCAPE EXPLOSION STATE
        void escapeExplosionState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;

        // PUT BOMB STATE
        void putBombState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;

        // WAITING STATE
        void waitingState(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;

        // Not useful

        // UTILS
        void moveAI(AIControllerComponent &ai, irr::core::vector2df &aiPos) const;
        bool hasReachedObjective(AIControllerComponent &ai, irr::core::vector2df &aiPos) const noexcept;
        void setNewShortObjective(is::components::AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;
        bool isAirBlock(is::ecs::Entity::Layer) const;
        bool hasAlreadyPass(std::vector<irr::core::vector2di> &moves, irr::core::vector2di &pos) const noexcept;
        int aiSearchPath(is::components::AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos) const;
        bool aiSearchPathRecursive(is::components::AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos, irr::core::vector2di dir) const;
        bool isInDanger(irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const;

    private:
        std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

        using state_function_t = void (AIControllerSystem::*)(is::components::AIControllerComponent &ai, irr::core::vector2df &aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;
        std::map<AIControllerComponent::AIState, state_function_t> _mapFunctionState;
    };

}

#endif /* !AIControllerSYSTEM_HPP_ */

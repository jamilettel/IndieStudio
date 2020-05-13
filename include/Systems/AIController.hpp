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
        // Not useful
        void setNewLongObjective(is::components::AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const;
        int aiSearchPath(is::components::AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos) const;
        bool aiSearchPathRecursive(is::components::AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos, irr::core::vector2di dir) const;
        bool isInDanger(irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const;
        
        // USEFUL
        void setNewShortObjective(is::components::AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;
        bool isAirBlock(is::ecs::Entity::Layer) const;
        bool canHideFromExplosion(AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map, irr::core::vector2di pos, irr::core::vector2di lastPos) const;
        bool findBombEmplacement(AIControllerComponent &ai, irr::core::vector2di newPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map, irr::core::vector2di lastPos) const;
        bool bombPosIsUseful(irr::core::vector2di &bombPos, std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;
        void moveAI(AIControllerComponent &ai, irr::core::vector2df &aiPos) const;
        bool hasReachedObjective(AIControllerComponent &ai, irr::core::vector2df &aiPos) const noexcept;
    
    private:
        std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

    };

}

#endif /* !AIControllerSYSTEM_HPP_ */

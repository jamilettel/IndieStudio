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

        void setNewShortObjective(is::components::AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map);
        void setNewLongObjective(is::components::AIControllerComponent &ai, irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map);
        int aiSearchPath(is::components::AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos);
        bool aiSearchPathRecursive(is::components::AIControllerComponent &ai, std::vector<std::vector<is::ecs::Entity::Layer>> map, irr::core::vector2di aiPos, irr::core::vector2di dir);
        bool isAirBlock(is::ecs::Entity::Layer);
        bool isInDanger(irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const;
    private:
        std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

    };

}

#endif /* !AIControllerSYSTEM_HPP_ */

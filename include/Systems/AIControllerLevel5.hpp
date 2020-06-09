/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIController
*/

#ifndef AIControllerSYSTEM_HPP_
#define AIControllerSYSTEM_HPP_

#include "AIControllerUtils.hpp"

#include "ECS/ASystem.hpp"
#include "Components/AIController.hpp"
#include "Components/CharacterController.hpp"
#include "Components/Window.hpp"
#include "Components/Movement.hpp"
#include "Components/Transform.hpp"
#include "Components/Time.hpp"
#include "Components/Bomb.hpp"
#include "AStarAlgorithm.hpp"
#include "ECS/Component.hpp"
#include "Components/Bomberman.hpp"

#include <cmath>

namespace is::systems {

    class AIControllerLevel5System : public is::ecs::ASystem {
    public:
        AIControllerLevel5System() = default;
        ~AIControllerLevel5System() override = default;

        AIControllerLevel5System(const AIControllerLevel5System &) = default;
        AIControllerLevel5System &operator=(const AIControllerLevel5System &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

    private:
        // NONE STATE
        void noneState(
            is::components::AIControllerComponent &ai,
            irr::core::vector2df &aiPos,
            std::vector<std::vector<is::ecs::Entity::Layer>> &map,
            std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
        ) const;
        void setNewLongObjective(
            is::components::AIControllerComponent &ai,
            irr::core::vector2di aiPos,
            std::vector<std::vector<is::ecs::Entity::Layer>> map,
            std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
        ) const;
        bool findBombEmplacement(
            AIControllerComponent &ai,
            const irr::core::vector2di &pos,
            const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
            const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
        ) const;
        bool canHideFromExplosion(
            AIControllerComponent &ai,
            const irr::core::vector2di &pos,
            const std::vector<std::vector<is::ecs::Entity::Layer>> &map
        ) const;
        [[nodiscard]] bool bombPosIsUseful(
            const AIControllerComponent &ai,
            const irr::core::vector2di &bombPos,
            const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
            const irr::core::vector2di &aiPos,
            const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
        ) const;
        [[nodiscard]] bool posIsHideFromBombs(const AIControllerComponent &ai, const irr::core::vector2di &aiPos, const std::vector<std::vector<is::ecs::Entity::Layer>> &map) const;
        [[nodiscard]] bool posIsHideFromABomb(
            const irr::core::vector2di &aiPos,
            const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
            const irr::core::vector2di &bombPos,
            const BombermanComponent &bomberman,
            int bombSize
        ) const noexcept;

        // ESCAPE EXPLOSION STATE
        void escapeExplosionState(
            is::components::AIControllerComponent &ai,
            irr::core::vector2df &aiPos,
            std::vector<std::vector<is::ecs::Entity::Layer>> &map,
            std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
        ) const;

        // PUT BOMB STATE
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

        // UTILS
        [[nodiscard]] bool isInDanger(irr::core::vector2di aiPos, std::vector<std::vector<is::ecs::Entity::Layer>> map) const;
        [[nodiscard]] bool bombPosAimForPlayer(
            const is::components::AIControllerComponent &ai,
            const irr::core::vector2di &bombPos,
            const std::vector<std::vector<is::ecs::Entity::Layer>> &map,
            const std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents
        ) const;

        [[nodiscard]] int getSizeBomb(const std::vector<std::shared_ptr<Component>> &bombs, const irr::core::vector2di &pos) const;

    private:
        std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

        using state_function_t = void (AIControllerLevel5System::*)(
            is::components::AIControllerComponent &ai,
            irr::core::vector2df &aiPos,
            std::vector<std::vector<is::ecs::Entity::Layer>> &map,
            std::vector<std::shared_ptr<is::ecs::Component>> &aiComponents) const;
        std::map<AIControllerComponent::AIState, state_function_t> _mapFunctionState;

        int _mapX = 13;
        int _mapY = 15;
    };

}

#endif /* !AIControllerSYSTEM_HPP_ */

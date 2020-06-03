/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** EndGame
*/

#ifndef ENDGAMESYSTEM_HPP_
#define ENDGAMESYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/AIController.hpp"
#include "Components/CharacterController.hpp"
#include "Components/Timer.hpp"
#include "Components/Rules.hpp"

namespace is::systems
{
    class EndGameSystem : public is::ecs::ASystem {
        public:
            EndGameSystem() = default;
            ~EndGameSystem() override = default;

            EndGameSystem(const EndGameSystem &) = default;
            EndGameSystem &operator=(const EndGameSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

        private:
    };
}


#endif /* !ENDGAME_HPP_ */

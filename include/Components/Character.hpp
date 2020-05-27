/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Character
*/

#ifndef CHARACTERCOMPONENT_HPP_
#define CHARACTERCOMPONENT_HPP_

#include "PresetAction.hpp"
#include "ECS/Component.hpp"

namespace is::components
{


    class CharacterComponent : public is::ecs::Component {
        public:
            enum Type {
                AI,
                KEYBOARD_PLAYER,
                JOYSTICK_PLAYER,
                MULTIPLAYER_PLAYER
            };

            static inline const PresetAction playerActions[7] = {
                {"MoveVerticalAxis", 1, "Move forward"},
                {"MoveVerticalAxis", -1, "Move backward"},
                {"MoveHorizontalAxis", -1, "Move right"},
                {"MoveHorizontalAxis", 1, "Move left"},
                {"DropBomb", 1, "Drop bomb"},
                {"Jump", 1, "Jump"},
                {"", -9999, ""},
            };

        public:
            CharacterComponent(std::shared_ptr<is::ecs::Entity> &e, int characterNumber);
            ~CharacterComponent() override = default;

            void setTimePlaying(size_t time) noexcept;
            void setNbBombPosed(size_t nbBombPosed) noexcept;
            void setNbBonusCollected(size_t nbBonusCollected) noexcept;
            void setNbCharactersKilled(size_t nbCharactersKilled) noexcept;

            [[nodiscard]] int getTimePlaying() const noexcept;
            [[nodiscard]] int getNbBombPosed() const noexcept;
            [[nodiscard]] int getNbBonueCollected() const noexcept;
            [[nodiscard]] int getNbCharactersKilled() const noexcept;
            [[nodiscard]] bool isAI() const noexcept;

            void deleteComponent() override;
            void reset() noexcept;

            int number;

            Type characterType = AI;

            int joystickId = -1;
            int presetNumber = -1;
            int multiplayerId = -1;

        private:
            size_t _timePlaying = 0;
            size_t _nbBombPosed = 0;
            size_t _nbBonusCollected = 0;
            size_t _nbCharactersKilled = 0;
    };
}

#endif /* !CHARACTERCOMPONENT_HPP_ */

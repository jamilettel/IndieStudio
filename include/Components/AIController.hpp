/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Keyboard Input
*/

#ifndef AIControllerCOMPONENT_HPP_
#define AIControllerCOMPONENT_HPP_

#include <string>

#include "Components/InputManager.hpp"
#include "EventManager/EventManager.hpp"

namespace is::components {

    class AIControllerComponent: public is::ecs::Component {
    public:
        AIControllerComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            InputManagerComponent &inputManager
            );
        ~AIControllerComponent() override = default;

        AIControllerComponent(const AIControllerComponent &) = delete;
        AIControllerComponent &operator=(const AIControllerComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] InputManagerComponent &getInputManager() const;

        irr::core::vector2di shortObjective;
        irr::core::vector2di lastShortObjective;
        irr::core::vector2di longObjective;
        bool needObjective;
        bool firstObjective;
        std::vector<irr::core::vector2di> lastMoves;

        float timeBeforeBegin; // temp
        bool isEscaping = false;
        bool needLongObjective = true;
        std::vector<std::pair<int, int>> path;

        enum AIState {
            NONE,
            WAITING,
            PUT_BOMB,
            ESCAPE_EXPLOSION
        };

        AIState state = NONE;
        irr::core::vector2di posToEscape;

    private:
        InputManagerComponent &_inputManager;
    };

}

#endif /* !AIControllerCOMPONENT_HPP_ */

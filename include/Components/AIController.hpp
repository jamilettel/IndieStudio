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
#include "Exception.hpp"

namespace is::components {

    class AIControllerComponent: public is::ecs::Component {
    public:
        AIControllerComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            InputManagerComponent &inputManager,
            int level = 4
            );
        ~AIControllerComponent() override = default;

        AIControllerComponent(const AIControllerComponent &) = delete;
        AIControllerComponent &operator=(const AIControllerComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] InputManagerComponent &getInputManager() const;

        irr::core::vector2di shortObjective;
        irr::core::vector2di lastShortObjective;
        irr::core::vector2di longObjective;

        float timeBeforeBegin; // temp
        std::vector<std::pair<int, int>> path;

        enum AIState {
            NONE,
            WAITING,
            PUT_BOMB,
            ESCAPE_EXPLOSION,
            GET_POWERUP
        };

        AIState state = NONE;
        irr::core::vector2di posToEscape;
        irr::core::vector2di bombPos = irr::core::vector2di(-1);

        bool operator==(const is::components::AIControllerComponent &ai) const;

        int getLevel() const noexcept;
        bool waitTime = false;

    private:
        InputManagerComponent &_inputManager;
        int _id;
        int _level;
    };

}

#endif /* !AIControllerCOMPONENT_HPP_ */

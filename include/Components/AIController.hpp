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
        ~AIControllerComponent() = default;

        AIControllerComponent(const AIControllerComponent &) = delete;
        AIControllerComponent &operator=(const AIControllerComponent &) = delete;

        void deleteComponent() override;

        InputManagerComponent &getInputManager() const;

        bool offense;
        irr::core::vector2df objective;
        irr::core::vector2df lock;
        bool needObjective;

        float timeBeforeBegin;

    private:
        InputManagerComponent &_inputManager;
    };

}

#endif /* !AIControllerCOMPONENT_HPP_ */

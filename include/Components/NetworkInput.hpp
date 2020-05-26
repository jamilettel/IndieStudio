/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Network Input
*/

#ifndef NetworkINPUTCOMPONENT_HPP_
#define NetworkINPUTCOMPONENT_HPP_

#include <string>
#include "ECS/Component.hpp"
#include "Components/InputManager.hpp"

namespace is::components {
    class NetworkInputComponent: public is::ecs::Component {
    public:
        NetworkInputComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            InputManagerComponent &inputManager,
            int mulId
        );
        ~NetworkInputComponent() override = default;

        NetworkInputComponent(const NetworkInputComponent &) = delete;
        NetworkInputComponent &operator=(const NetworkInputComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] InputManagerComponent &getInputManager() const;

        int id;


    private:
        InputManagerComponent &_inputManager;

    };

}

#endif /* !NetworkINPUTCOMPONENT_HPP_ */

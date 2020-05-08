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
        std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;

    };

}

#endif /* !AIControllerSYSTEM_HPP_ */

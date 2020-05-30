/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Alert
*/

#ifndef ALERTSYSTEM_HPP_
#define ALERTSYSTEM_HPP_

#include "ECS/ASystem.hpp"
#include "Components/Alert.hpp"
#
namespace is::systems {

    class AlertSystem: public is::ecs::ASystem {
    public:
        AlertSystem() = default;
        ~AlertSystem() = default;

        AlertSystem(const AlertSystem &) = default;
        AlertSystem &operator=(const AlertSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

        void setDisabledButtons(bool disable, const is::components::ButtonComponent &dontDisable);

    protected:
    private:
        std::vector<std::shared_ptr<is::ecs::Component>> _disabledButtons;
    };

}

#endif /* !ALERTSYSTEM_HPP_ */

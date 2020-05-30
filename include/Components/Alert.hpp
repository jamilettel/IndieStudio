/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Alert
*/

#ifndef ALERTCOMPONENT_HPP_
#define ALERTCOMPONENT_HPP_

#include "ECS/Entity.hpp"
#include "Components/Button.hpp"
#include "Components/Image.hpp"
#include <string>
#include <vector>

namespace is::components {

    class AlertComponent: is::ecs::Component {
    public:
        AlertComponent(std::shared_ptr<is::ecs::Entity> &e);
        ~AlertComponent() = default;

        AlertComponent(const AlertComponent &) = delete;
        AlertComponent &operator=(const AlertComponent &) = delete;

        void addAlert(const std::string &alert);

        void acceptAlert();
        bool hasAlert() const;

        size_t getQueueLength() const;

        void setNextAlert();

        const std::string &getCurrentAlert() const;

    private:
        ImageComponent &_image;
        ButtonComponent &_button;
        std::string _alert;
        std::vector<std::string> _queue;

        bool _hasAlert = false;
    };

}

#endif /* !ALERTCOMPONENT_HPP_ */
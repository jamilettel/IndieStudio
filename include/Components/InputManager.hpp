/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Input Manager
*/

#ifndef INPUTMANAGERCOMPONENT_HPP_
#define INPUTMANAGERCOMPONENT_HPP_

#include "ECS/Component.hpp"
#include <map>
#include <string>

namespace is::components {

    class InputManagerComponent: public is::ecs::Component {
    public:
        explicit InputManagerComponent(
            std::shared_ptr<is::ecs::Entity> &e
            );
        ~InputManagerComponent() override = default;

        InputManagerComponent(const InputManagerComponent &) = delete;
        InputManagerComponent &operator=(const InputManagerComponent &) = delete;

        void resetValues();
        void setValue(const std::string &action, float value);
        void addValue(const std::string &action, float value);
        [[nodiscard]] float getInput(const std::string &action) const;

        void deleteComponent() override;

    private:
        std::map<std::string, float> _actions;
    };

}

#endif /* !INPUTMANAGERCOMPONENT_HPP_ */

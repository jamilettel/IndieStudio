/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Input Manager
*/

#ifndef INPUTMANAGERCOMPONENT_HPP_
#define INPUTMANAGERCOMPONENT_HPP_

#include <functional>
#include <map>
#include <string>
#include <algorithm>

#include "ECS/Component.hpp"

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
            void resetValue(const std::string &action);
            void setValue(const std::string &action, float value);
            void addValue(const std::string &action, float value);
            [[nodiscard]] float getInput(const std::string &action) const;

            bool isActionSet(const std::string &action);

            void deleteComponent() override;

        private:
            std::map<std::string, float> _actions;
    };

}

#endif /* !INPUTMANAGERCOMPONENT_HPP_ */

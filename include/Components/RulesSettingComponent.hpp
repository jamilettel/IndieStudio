/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RulesSettingComponent
*/

#ifndef RULESSETTINGCOMPONENT_HPP_
#define RULESSETTINGCOMPONENT_HPP_

#include <functional>

#include "ECS/Component.hpp"

namespace is::components
{
    class RulesSettingComponent : public is::ecs::Component {
        
        public:
            using onSelectFct = std::function<void()>;
            using onExitFct = std::function<void()>;

        public:
            RulesSettingComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~RulesSettingComponent() = default;

            void addRule(std::function<void()> onSelect, std::function<void()> onExit);
            void up();
            void down();
            int getIndex() const noexcept;

            void deleteComponent() override;

        private:
            int _i = 0;
            std::vector<std::pair<onSelectFct, onExitFct>> _rules;
    };
}


#endif /* !RULESSETTINGCOMPONENT_HPP_ */

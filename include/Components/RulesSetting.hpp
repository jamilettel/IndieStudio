/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RulesSettingComponent
*/

#ifndef RULESSETTINGCOMPONENT_HPP_
#define RULESSETTINGCOMPONENT_HPP_

#include <functional>
#include <vector>
#include <string>

#include "ECS/Component.hpp"

namespace is::components
{
    class RulesSettingComponent : public is::ecs::Component {
        
        public:
            using onSelectFct = std::function<void()>;
            using onExitFct = std::function<void()>;
            using onDisappear = std::function<void()>;
            using onRuleUp = std::function<void()>;
            using onRuleDown = std::function<void()>;
            using onAppear = std::function<void()>;

        public:
            RulesSettingComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~RulesSettingComponent() = default;

            void addRule(
                std::function<void()> onSelect,
                std::function<void()> onExit,
                std::function<void()> onDisappear,
                std::function<void()> onRuleUp,
                std::function<void()> onRuleDown,
                std::function<void()> onAppear
            );
            void up();
            void down();
            int getIndex() const noexcept;
            int getFirst() const noexcept;
            int getLast() const noexcept;

            void deleteComponent() override;

        private:
            int _i = 0;
            std::vector<std::tuple<onSelectFct, onExitFct, onDisappear, onRuleUp, onRuleDown, onAppear>> _rules;
            int _first = 0;
            int _last = 0;
    };
}


#endif /* !RULESSETTINGCOMPONENT_HPP_ */

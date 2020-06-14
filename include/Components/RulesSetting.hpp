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
#include <algorithm>

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
            using onReset = std::function<void()>;

        public:
            explicit RulesSettingComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~RulesSettingComponent() override = default;

            void addRule(
                const std::function<void()>& onSelect,
                const std::function<void()>& onExit,
                const std::function<void()>& onDisappear,
                const std::function<void()>& onRuleUp,
                const std::function<void()>& onRuleDown,
                const std::function<void()>& onAppear,
                const std::function<void()>& onReset
            );
            void up();
            void down();
            [[nodiscard]] int getIndex() const noexcept;
            [[nodiscard]] int getFirst() const noexcept;
            [[nodiscard]] int getLast() const noexcept;

            void deleteComponent() override;
            void reset();

        private:
            int _i = 0;
            int _first = 0;
            int _last = 0;
            std::vector<std::tuple<onSelectFct, onExitFct, onDisappear, onRuleUp, onRuleDown, onAppear, onReset>> _rules;
    };
}


#endif /* !RULESSETTINGCOMPONENT_HPP_ */

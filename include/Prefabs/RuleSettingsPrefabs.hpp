/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsPrefabs
*/

#ifndef RULESETTINGSPREFABS_HPP_
#define RULESETTINGSPREFABS_HPP_

#include "ECS/Entity.hpp"
#include "Game.hpp"

#include "Components/Texture.hpp"
#include "Components/Button.hpp"
#include "Components/RulesSetting.hpp"
#include "Components/Text.hpp"
#include "Components/Rules.hpp"

#include <irrlicht.h>

#include <memory>

namespace is::prefabs
{
    class RuleSettingsPrefabs {
        public:
            static std::shared_ptr<is::ecs::Entity> createBackground();
            static std::shared_ptr<is::ecs::Entity> createReturnButton();
            static std::shared_ptr<is::ecs::Entity> createRuleSettings();
            static std::shared_ptr<is::ecs::Entity> createSettingsBackground(is::components::RulesSettingComponent &component);
            static std::shared_ptr<is::ecs::Entity> createNumberOfPlayersRule(is::components::RulesSettingComponent &component, is::components::RulesComponent &rules);
            static std::shared_ptr<is::ecs::Entity> createIconsRule(is::components::RulesSettingComponent &component, is::components::RulesComponent &rules);
            static std::shared_ptr<is::ecs::Entity> createMaxTimeRule(is::components::RulesSettingComponent &component, is::components::RulesComponent &rules);
            static std::shared_ptr<is::ecs::Entity> createModeFpsRule(is::components::RulesSettingComponent &component, is::components::RulesComponent &rules);

        private:
    };
}


#endif /* !RULESETTINGSPREFABS_HPP_ */

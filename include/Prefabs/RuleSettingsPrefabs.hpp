/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsPrefabs
*/

#ifndef RULESETTINGSPREFABS_HPP_
#define RULESETTINGSPREFABS_HPP_

#include "ECS/Entity.hpp"

#include "Components/Texture.hpp"
#include "Components/Button.hpp"

#include <irrlicht.h>

#include <memory>

namespace is::prefabs
{
    class RuleSettingsPrefabs {
        public:
            static std::shared_ptr<is::ecs::Entity> createBackground();
            static std::shared_ptr<is::ecs::Entity> createSaveButton();
            static std::shared_ptr<is::ecs::Entity> createReturnButton();
            static std::shared_ptr<is::ecs::Entity> createSettingsBackground();
            static std::shared_ptr<is::ecs::Entity> createNumberOfPlayersRule();

        private:
    };
}


#endif /* !RULESETTINGSPREFABS_HPP_ */

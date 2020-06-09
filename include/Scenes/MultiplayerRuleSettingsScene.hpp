/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** MultiplayerRuleSettingsScene
*/

#ifndef MULTIPLAYERRULESETTINGSSCENE_HPP_
#define MULTIPLAYERRULESETTINGSSCENE_HPP_

#include "ECS/AScene.hpp"

#include "Systems/Time.hpp"
#include "Systems/Audio.hpp"
#include "Systems/Window.hpp"
#include "Systems/Image.hpp"
#include "Systems/Button.hpp"
#include "Systems/Text.hpp"
#include "Systems/Cursor.hpp"
#include "Systems/Network.hpp"

namespace is::scenes
{
    class MultiplayerRuleSettingsScene : public is::ecs::AScene {
        public:
            MultiplayerRuleSettingsScene();
            ~MultiplayerRuleSettingsScene() override = default;

            MultiplayerRuleSettingsScene(const MultiplayerRuleSettingsScene &scene) = default;
            MultiplayerRuleSettingsScene &operator=(const MultiplayerRuleSettingsScene &scene) = default;

            void initSystems() override;
            void initEntities() override;

        private:
            is::components::RulesComponent &getRulesComponent() const;
    };
}


#endif /* !MULTIPLAYERRULESETTINGSSCENE_HPP_ */

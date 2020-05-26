/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsScene
*/

#ifndef RULESETTINGSSCENE_HPP_
#define RULESETTINGSSCENE_HPP_

#include "ECS/AScene.hpp"

#include "Systems/Audio.hpp"
#include "Systems/Time.hpp"
#include "Systems/Window.hpp"
#include "Systems/Light.hpp"
#include "Systems/Camera.hpp"
#include "Systems/Image.hpp"
#include "Systems/Button.hpp"
#include "Systems/Cursor.hpp"
#include "Prefabs/GlobalPrefabs.hpp"
#include "Prefabs/EndGamePrefabs.hpp"
#include "Systems/ModelRenderer.hpp"
#include "Systems/Texture.hpp"
#include "Systems/Text.hpp"

#include "Components/RulesSettingComponent.hpp"

#include "Prefabs/RuleSettingsPrefabs.hpp"

namespace is::scenes
{
    class RuleSettingsScene : public is::ecs::AScene {
        public:
            RuleSettingsScene();
            ~RuleSettingsScene() override = default;

            RuleSettingsScene(const RuleSettingsScene &) = default;
            RuleSettingsScene &operator=(const RuleSettingsScene &) = default;

            void initSystems() override;
            void initEntities() override;

        private:
    };
}


#endif /* !RULESETTINGSSCENE_HPP_ */

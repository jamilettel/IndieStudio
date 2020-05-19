/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef PRESETSELECTIONSCENE_HPP_
#define PRESETSELECTIONSCENE_HPP_

#include "Systems/Time.hpp"
#include "Systems/Audio.hpp"
#include "Systems/Light.hpp"
#include "Systems/Window.hpp"
#include "Systems/Camera.hpp"
#include "Systems/Image.hpp"
#include "Systems/Button.hpp"
#include "Systems/Text.hpp"
#include "Systems/Cursor.hpp"
#include "Prefabs/GlobalPrefabs.hpp"
#include "ECS/AScene.hpp"

namespace is::scenes {

    class PresetSelectionScene : public is::ecs::AScene {
        public:
            PresetSelectionScene();
            ~PresetSelectionScene() override = default;

            PresetSelectionScene(const PresetSelectionScene &) = default;
            PresetSelectionScene &operator=(const PresetSelectionScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !PRESETSELECTIONSCENE_HPP_ */

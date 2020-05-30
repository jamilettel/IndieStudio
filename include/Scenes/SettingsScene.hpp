/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef SETTINGSSCENE_HPP_
#define SETTINGSSCENE_HPP_

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
#include "Systems/JoystickInput.hpp"
#include "Systems/JoystickCursor.hpp"
#include "Systems/Alert.hpp"

namespace is::scenes {

    class SettingsScene : public is::ecs::AScene {
        public:
            SettingsScene();
            ~SettingsScene() override = default;

            SettingsScene(const SettingsScene &) = default;
            SettingsScene &operator=(const SettingsScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !SETTINGSSCENE_HPP_ */

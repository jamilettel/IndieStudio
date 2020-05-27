/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef MAINMENUSCENE_HPP_
#define MAINMENUSCENE_HPP_

#include "Systems/Time.hpp"
#include "Systems/Audio.hpp"
#include "Systems/Light.hpp"
#include "Systems/Window.hpp"
#include "Systems/Camera.hpp"
#include "Systems/Image.hpp"
#include "Systems/Button.hpp"
#include "Prefabs/GlobalPrefabs.hpp"
#include "ECS/AScene.hpp"
#include "Systems/Cursor.hpp"
#include "Systems/JoystickInput.hpp"
#include "Systems/JoystickCursor.hpp"

namespace is::scenes {

    class MainMenuScene : public is::ecs::AScene {
        public:
            MainMenuScene();
            ~MainMenuScene() override = default;

            MainMenuScene(const MainMenuScene &) = default;
            MainMenuScene &operator=(const MainMenuScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !MAINMENUSCENE_HPP_ */

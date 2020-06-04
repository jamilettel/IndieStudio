/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef PAUSESCENE_HPP_
#define PAUSESCENE_HPP_

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
#include "Systems/Pause.hpp"

namespace is::scenes {

    class PauseScene : public is::ecs::AScene {
        public:
            PauseScene();
            ~PauseScene() override = default;

            PauseScene(const PauseScene &) = default;
            PauseScene &operator=(const PauseScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !PAUSESCENE_HPP_ */

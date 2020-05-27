/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef RECORDSCENE_HPP_
#define RECORDSCENE_HPP_

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

namespace is::scenes {

    class RecordScene : public is::ecs::AScene {
        public:
            RecordScene();
            ~RecordScene() override = default;

            RecordScene(const RecordScene &) = default;
            RecordScene &operator=(const RecordScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !RECORDSCENE_HPP_ */

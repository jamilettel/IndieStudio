/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef HOWTOPLAYSCENE_HPP_
#define HOWTOPLAYSCENE_HPP_

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

    class HowToPlayScene : public is::ecs::AScene {
        public:
            HowToPlayScene();
            ~HowToPlayScene() override = default;

            HowToPlayScene(const HowToPlayScene &) = default;
            HowToPlayScene &operator=(const HowToPlayScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !HOWTOPLAYSCENE_HPP_ */

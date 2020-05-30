/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef CREDITSCENE_HPP_
#define CREDITSCENE_HPP_

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

    class CreditScene : public is::ecs::AScene {
        public:
            CreditScene();
            ~CreditScene() override = default;

            CreditScene(const CreditScene &) = default;
            CreditScene &operator=(const CreditScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !CREDITSCENE_HPP_ */

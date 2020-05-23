/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef MultiplayerScene_HPP_
#define MultiplayerScene_HPP_

#include "Systems/Time.hpp"
#include "Systems/Audio.hpp"
#include "Systems/Light.hpp"
#include "Systems/Window.hpp"
#include "Systems/Camera.hpp"
#include "Systems/Image.hpp"
#include "Systems/Button.hpp"
#include "Systems/Text.hpp"
#include "Systems/Cursor.hpp"
#include "Systems/Network.hpp" 
#include "Prefabs/GlobalPrefabs.hpp"
#include "Components/Network.hpp"
#include "ECS/AScene.hpp"

namespace is::scenes {

    class MultiplayerScene : public is::ecs::AScene {
        public:
            MultiplayerScene();
            ~MultiplayerScene() override = default;

            MultiplayerScene(const MultiplayerScene &) = default;
            MultiplayerScene &operator=(const MultiplayerScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !MultiplayerScene_HPP_ */

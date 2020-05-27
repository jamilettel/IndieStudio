/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef MultiplayerLobbyScene_HPP_
#define MultiplayerLobbyScene_HPP_

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

    class MultiplayerLobbyScene : public is::ecs::AScene {
        public:
            MultiplayerLobbyScene();
            ~MultiplayerLobbyScene() override = default;

            MultiplayerLobbyScene(const MultiplayerLobbyScene &) = default;
            MultiplayerLobbyScene &operator=(const MultiplayerLobbyScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !MultiplayerLobbyScene_HPP_ */

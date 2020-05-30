/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef MultiplayerLobbyChoiceScene_HPP_
#define MultiplayerLobbyChoiceScene_HPP_

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
#include "Systems/Alert.hpp"

namespace is::scenes {

    class MultiplayerLobbyChoiceScene : public is::ecs::AScene {
        public:
            MultiplayerLobbyChoiceScene();
            ~MultiplayerLobbyChoiceScene() override = default;

            MultiplayerLobbyChoiceScene(const MultiplayerLobbyChoiceScene &) = default;
            MultiplayerLobbyChoiceScene &operator=(const MultiplayerLobbyChoiceScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !MultiplayerLobbyChoiceScene_HPP_ */

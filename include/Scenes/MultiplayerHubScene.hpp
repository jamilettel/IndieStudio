/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef MultiplayerHubScene_HPP_
#define MultiplayerHubScene_HPP_

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

    class MultiplayerHubScene : public is::ecs::AScene {
        public:
            MultiplayerHubScene();
            ~MultiplayerHubScene() override = default;

            MultiplayerHubScene(const MultiplayerHubScene &) = default;
            MultiplayerHubScene &operator=(const MultiplayerHubScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !MultiplayerHubScene_HPP_ */

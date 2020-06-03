/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef MultiplayerGameScene_HPP_
#define MultiplayerGameScene_HPP_

#include "ECS/AScene.hpp"
#include "Systems/Window.hpp"
#include "Systems/Camera.hpp"
#include "Systems/ModelRenderer.hpp"
#include "Systems/CharacterController.hpp"
#include "Systems/Light.hpp"
#include "Systems/Audio.hpp"
#include "Systems/Movement.hpp"
#include "Systems/Gravity.hpp"
#include "Systems/Bomb.hpp"
#include "Systems/Fire.hpp"
#include "Systems/Time.hpp"
#include "Systems/Button.hpp"
#include "Systems/Text.hpp"
#include "Systems/Slider.hpp"
#include "Systems/Image.hpp"
#include "Systems/PowerUp.hpp"
#include "Systems/Jump.hpp"
#include "Systems/KeyboardInput.hpp"
#include "Systems/AIControllerLevel5.hpp"
#include "Components/Window.hpp"
#include "Prefabs/GlobalPrefabs.hpp"
#include "MapGenerator.hpp"
#include "Systems/JoystickInput.hpp"
#include "Systems/Particule.hpp"
#include "Systems/Cursor.hpp"
#include "Systems/EndGame.hpp"
#include "Systems/JoystickCursor.hpp"
#include "Systems/Network.hpp"
#include "Systems/NetworkInput.hpp"
#include "Systems/Alert.hpp"

namespace is::scenes {

    class MultiplayerGameScene : public is::ecs::AScene {
        public:
            MultiplayerGameScene();
            ~MultiplayerGameScene() override = default;

            MultiplayerGameScene(const MultiplayerGameScene &) = default;
            MultiplayerGameScene &operator=(const MultiplayerGameScene &) = default;

            void initSystems() override;
            void initEntities() override;

            void awake() override;
            void onTearDown() override;
    };

}

#endif /* !MultiplayerGameScene_HPP_ */

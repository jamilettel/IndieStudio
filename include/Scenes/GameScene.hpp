/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameScene
*/

#ifndef GAMESCENE_HPP_
#define GAMESCENE_HPP_

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
#include "Systems/AIController.hpp"
#include "Components/Window.hpp"
#include "Prefabs/GlobalPrefabs.hpp"
#include "MapGenerator.hpp"
#include "Systems/JoystickInput.hpp"
#include "Systems/Particule.hpp"

namespace is::scenes {

    class GameScene : public is::ecs::AScene {
        public:
            GameScene();
            ~GameScene() override = default;

            GameScene(const GameScene &) = default;
            GameScene &operator=(const GameScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !GAMESCENE_HPP_ */

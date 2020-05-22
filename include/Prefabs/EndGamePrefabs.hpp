/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** SceneEndGamePrefabs
*/

#ifndef ENDGAMEPREFABS_HPP_
#define ENDGAMEPREFABS_HPP_

#include "ECS/Entity.hpp"
#include "ECS/AScene.hpp"

#include "Game.hpp"

#include "Components/Image.hpp"
#include "Components/Animator.hpp"
#include "Components/Transform.hpp"
#include "Components/Texture.hpp"
#include "Components/Button.hpp"
#include "Components/Text.hpp"

#include <memory>

namespace is::prefabs
{
    class EndGamePrefabs {
        public:
    
            static std::shared_ptr<is::ecs::Entity> createBackground();
            static std::shared_ptr<is::ecs::Entity> createPlayer();
            static std::shared_ptr<is::ecs::Entity> createPlayer2();
            static std::shared_ptr<is::ecs::Entity> createPlayer3();
            static std::shared_ptr<is::ecs::Entity> createPlayer4();

            static std::shared_ptr<is::ecs::Entity> createWindow(double posX);

            static std::shared_ptr<is::ecs::Entity> createContinueButton(int posX);

            static std::shared_ptr<is::ecs::Entity> createBackwardButton(int posX);
            static std::shared_ptr<is::ecs::Entity> createForwardButton(int posX);

            static std::shared_ptr<is::ecs::Entity> createHighTable(double posX);
            static std::shared_ptr<is::ecs::Entity> createLowTable(double posX);

            static std::shared_ptr<is::ecs::Entity> createMedal1(double posX);
            static std::shared_ptr<is::ecs::Entity> createMedal2(double posX);
            static std::shared_ptr<is::ecs::Entity> createMedal3(double posX);
    };
}


#endif /* !SCENEENDGAMEPREFABS_HPP_ */

/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** SceneEndGamePrefabs
*/

#ifndef ENDGAMEPREFABS_HPP_
#define ENDGAMEPREFABS_HPP_

#include "ECS/Entity.hpp"

#include "Components/Image.hpp"
#include "Components/Animator.hpp"
#include "Components/Transform.hpp"
#include "Components/Texture.hpp"

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

            static std::shared_ptr<is::ecs::Entity> createWindow();
            static std::shared_ptr<is::ecs::Entity> createWindow2();
            static std::shared_ptr<is::ecs::Entity> createWindow3();
            static std::shared_ptr<is::ecs::Entity> createWindow4();
    };
}


#endif /* !SCENEENDGAMEPREFABS_HPP_ */

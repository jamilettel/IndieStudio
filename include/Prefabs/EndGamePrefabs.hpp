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
#include "Components/Stats.hpp"

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
        
        private:
            static void addWindow(std::shared_ptr<is::ecs::Entity> &e, double posX);
            static void addContinueButton(std::shared_ptr<is::ecs::Entity> &e, int posX);
            static void addBackwardButton(std::shared_ptr<is::ecs::Entity> &e, int posX);
            static void addForwardButton(std::shared_ptr<is::ecs::Entity> &e, int posX);
            static void addHighTable(std::shared_ptr<is::ecs::Entity> &e, double posX);
            static void addLowTable(std::shared_ptr<is::ecs::Entity> &e, double posX);
            static void addMedal(std::shared_ptr<is::ecs::Entity> &e, double posX, const std::string &filename);
            static is::components::TextComponent &addTextHigh(std::shared_ptr<is::ecs::Entity> &e, int posX);
            static is::components::TextComponent &addTextLow(std::shared_ptr<is::ecs::Entity> &e, int posX);
            static void addStatsPlayer(std::shared_ptr<is::ecs::Entity> &e, is::components::TextComponent &textHigh, is::components::TextComponent &textLow);
    };
}


#endif /* !SCENEENDGAMEPREFABS_HPP_ */

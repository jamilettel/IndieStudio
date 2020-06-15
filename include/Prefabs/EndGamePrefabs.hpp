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

namespace is::prefabs
{
    class EndGamePrefabs {
        public:
    
            static std::shared_ptr<is::ecs::Entity> createBackground();
            static std::shared_ptr<is::ecs::Entity> createPlayer(
                std::vector<std::pair<std::string, std::string>> &infos,
                bool isAI,
                const std::string &texture,
                float posWindow,
                std::pair<float, float> &posModelPlayer,
                int position
            );
        
        private:
            static void addWindow(std::shared_ptr<is::ecs::Entity> &e, double posX);
            static void addContinueButton(std::shared_ptr<is::ecs::Entity> &e, float posX, is::components::TextComponent &text, bool isAI);
            static void addBackwardButton(std::shared_ptr<is::ecs::Entity> &e, float posX);
            static void addForwardButton(std::shared_ptr<is::ecs::Entity> &e, float posX);
            static void addHighTable(std::shared_ptr<is::ecs::Entity> &e, double posX);
            static void addLowTable(std::shared_ptr<is::ecs::Entity> &e, double posX);
            static void addMedal(std::shared_ptr<is::ecs::Entity> &e, double posX, const std::string &filename);
            static is::components::TextComponent &addTextHigh(std::shared_ptr<is::ecs::Entity> &e, float posX);
            static is::components::TextComponent &addTextLow(std::shared_ptr<is::ecs::Entity> &e, float posX);
            static void addStatsPlayer(
                std::shared_ptr<is::ecs::Entity> &e,
                is::components::TextComponent &textHigh,
                is::components::TextComponent &textLow,
                std::vector<std::pair<std::string, std::string>> &infos,
                int rank
            );
            static is::components::TextComponent &addWaitingText(std::shared_ptr<is::ecs::Entity> &e, float posX);
    };
}


#endif /* !SCENEENDGAMEPREFABS_HPP_ */

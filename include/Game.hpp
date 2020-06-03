/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include "ECS/IScene.hpp"

namespace is {

    class Game {
        public:
            Game() = default;
            ~Game() = default;

            Game(const Game &) = default;
            Game &operator=(const Game &) = default;

            void addScene(is::ecs::Scenes sceneType, const std::shared_ptr<is::ecs::IScene> &scene);
            void launchGame(is::ecs::Scenes startScene);
            void switchScene();

            static bool isRunning;
            static void setActualScene(is::ecs::Scenes, bool loadScene = true, bool destroyScene = true);
            static is::ecs::Scenes getPreviousScene();
            static is::ecs::Scenes getCurrentScene();

        private:
            std::map<is::ecs::Scenes, std::shared_ptr<is::ecs::IScene>> _scenes;
            static is::ecs::Scenes currentScene;
            static is::ecs::Scenes _previousScene;
            static bool _destroyScene;
            static bool _loadScene;
            is::ecs::Scenes changeScene;
    };

}

#endif /* !GAME_HPP_ */

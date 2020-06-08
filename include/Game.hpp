/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include <map>
#include "ECS/IScene.hpp"

#include "Scenes/SplashScreenScene.hpp"
#include "Scenes/MainMenuScene.hpp"
#include "Scenes/CreditScene.hpp"
#include "Scenes/HowToPlayScene.hpp"
#include "Scenes/PauseScene.hpp"
#include "Scenes/SettingsScene.hpp"
#include "Scenes/ControllersScene.hpp"
#include "Scenes/PresetSelectionScene.hpp"
#include "Scenes/MultiplayerHubScene.hpp"
#include "Scenes/MultiplayerLobbyChoiceScene.hpp"
#include "Scenes/MultiplayerLobbyScene.hpp"
#include "Scenes/MultiplayerGameScene.hpp"
#include "Scenes/GameScene.hpp"
#include "Scenes/EndGameScene.hpp"
#include "Scenes/RuleSettingsScene.hpp"

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
            void unloadScene();

            static bool isRunning;
            static void setActualScene(is::ecs::Scenes, bool loadScene = true, bool destroyScene = true);
            static is::ecs::Scenes getPreviousScene();
            static is::ecs::Scenes getCurrentScene();
            static void setUnloadScene(is::ecs::Scenes scene);

            static void addResource(const std::string &path, void *resource);
            static void *getResource(const std::string &path);
            static void resourcesInitialization(const std::shared_ptr<is::components::WindowComponent> &window);

        private:
            std::map<is::ecs::Scenes, std::shared_ptr<is::ecs::IScene>> _scenes;
            static is::ecs::Scenes currentScene;
            static is::ecs::Scenes _previousScene;
            static bool _destroyScene;
            static bool _loadScene;
            is::ecs::Scenes changeScene;
            static std::pair<bool, is::ecs::Scenes> _unloadScene;
            static std::map<std::string, std::shared_ptr<void *>> resources;
    };

}

#endif /* !GAME_HPP_ */

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Scene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "ECS/EntityManager.hpp"
#include "ECS/SystemManager.hpp"
#include "ECS/ComponentManager.hpp"

namespace is::ecs {

    enum Scenes {
        SCENE_SPLASH_SCREEN,
        SCENE_MAIN_MENU,
        SCENE_PAUSE,
        SCENE_CREDIT,
        SCENE_HOWTOPLAY,
        SCENE_RECORD,
        SCENE_SETTINGS,
        SCENE_CONTROLLERS,
        SCENE_PRESETSELECTION,
        SCENE_MULTIPLAYER_HUB,
        SCENE_MULTIPLAYER_LOBBY_CHOICE,
        SCENE_MULTIPLAYER_LOBBY,
        SCENE_MULTIPLAYER_GAME,
        SCENE_GAME,
        SCENE_ENDGAME,
        SCENE_RULE_SETTINGS,
        NOTHING
    };

    class IScene {
        public:
            virtual ~IScene() = default;

            virtual void initSystems() = 0;
            virtual void initEntities() = 0;

            virtual void awake() = 0;
            virtual void start() = 0;
            virtual void update() = 0;
            virtual void stop() = 0;
            virtual void onTearDown() = 0;
    };

}

#endif /* !ISCENE_HPP_ */

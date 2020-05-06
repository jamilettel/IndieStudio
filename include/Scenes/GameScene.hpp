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

#include "Components/Window.hpp"

#include "Prefabs/GlobalPrefabs.hpp"

class GameScene : public is::ecs::AScene {
    public:
        GameScene();
        ~GameScene();

        GameScene(const GameScene &) = default;
        GameScene &operator=(const GameScene &) = default;

        void initSystems();
        void initEntities();

    protected:
    private:
};

#endif /* !GAMESCENE_HPP_ */

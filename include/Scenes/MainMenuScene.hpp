/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#ifndef MAINMENUSCENE_HPP_
#define MAINMENUSCENE_HPP_

#include "ECS/AScene.hpp"

namespace is::scenes {

    class MainMenuScene : public is::ecs::AScene {
        public:
            MainMenuScene();
            ~MainMenuScene() override = default;

            MainMenuScene(const MainMenuScene &) = default;
            MainMenuScene &operator=(const MainMenuScene &) = default;

            void initSystems() override;
            void initEntities() override;

        protected:
        private:
    };

}

#endif //MAINMENUSCENE_HPP_

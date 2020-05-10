/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#ifndef SPLASHSCREENSCENE_HPP_
#define SPLASHSCREENSCENE_HPP_

#include "ECS/AScene.hpp"

namespace is::scenes {

    class SplashScreenScene : public is::ecs::AScene {
        public:
            SplashScreenScene();
            ~SplashScreenScene() override = default;

            SplashScreenScene(const SplashScreenScene &) = default;
            SplashScreenScene &operator=(const SplashScreenScene &) = default;

            void initSystems() override;
            void initEntities() override;

        protected:
        private:
    };

}

#endif //SPLASHSCREENSCENE_HPP_

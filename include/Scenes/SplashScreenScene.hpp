/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SplashScreen
*/

#ifndef SPLASHSCREENSCENE_HPP_
#define SPLASHSCREENSCENE_HPP_

#include "Systems/Time.hpp"
#include "Systems/Audio.hpp"
#include "Systems/Light.hpp"
#include "Systems/Window.hpp"
#include "Systems/Camera.hpp"
#include "Systems/Image.hpp"
#include "Prefabs/GlobalPrefabs.hpp"
#include "ECS/AScene.hpp"
#include "Systems/Cursor.hpp"

namespace is::scenes {

    class SplashScreenScene : public is::ecs::AScene {
        public:
            SplashScreenScene();
            ~SplashScreenScene() override = default;

            SplashScreenScene(const SplashScreenScene &) = default;
            SplashScreenScene &operator=(const SplashScreenScene &) = default;

            void start() override;
            void update() override;

            void initSystems() override;
            void initEntities() override;

        private:
            std::optional<std::reference_wrapper<is::components::TimeComponent>> _time;
    };

}

#endif /* !SPLASHSCREENSCENE_HPP_ */

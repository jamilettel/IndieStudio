/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemWindow
*/

#ifndef SystemWindow_HPP_
#define SystemWindow_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Window.hpp"

namespace is::systems {

    class SystemWindow : public is::ecs::ASystem {
        public:
            SystemWindow() = default;
            ~SystemWindow() = default;

            SystemWindow(const SystemWindow &) = default;
            SystemWindow &operator=(const SystemWindow &) = default;

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
        private:
    };

}

#endif /* !SystemWindow_HPP_ */

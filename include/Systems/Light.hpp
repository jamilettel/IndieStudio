/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemModelRenderer
*/

#ifndef SystemSystemLight_HPP_
#define SystemSystemLight_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <limits.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Light.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"

namespace is::systems {

    class SystemLight : public is::ecs::ASystem {
        public:
            SystemLight() = default;
            ~SystemLight() = default;

            SystemLight(const SystemLight &) = default;
            SystemLight &operator=(const SystemLight &) = default;

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
        private:
    };

}

#endif /* !SystemSystemLight_HPP_ */

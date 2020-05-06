/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemCamera
*/

#ifndef SystemCamera_HPP_
#define SystemCamera_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/Camera.hpp"
#include "Components/Window.hpp"


class SystemCamera : public is::ecs::ASystem {
    public:
        SystemCamera();
        ~SystemCamera();

        SystemCamera(const SystemCamera &) = default;
        SystemCamera &operator=(const SystemCamera &) = default;

        void awake();
        void start();
        void update();
        void stop();
        void onTearDown();

    protected:
    private:
};

#endif /* !SystemCamera_HPP_ */

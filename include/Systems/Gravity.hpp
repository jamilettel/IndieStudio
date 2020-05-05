/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gravity
*/

#ifndef GRAVITY_HPP_
#define GRAVITY_HPP_

#include "ECS/ISystem.hpp"

#include <iostream>

class Gravity : public is::ecs::ISystem {
    public:
        Gravity();
        ~Gravity();

        Gravity(const Gravity &) = default;
        Gravity &operator=(const Gravity &) = default;


        void awake();
        void start();
        void update();
        void stop();
        void onTearDown();

    protected:
    private:
};

#endif /* !GRAVITY_HPP_ */

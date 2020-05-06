/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemGravity
*/

#ifndef SystemGravity_HPP_
#define SystemGravity_HPP_

#include "ECS/ASystem.hpp"

#include <iostream>

class SystemGravity : public is::ecs::ASystem {
    public:
        SystemGravity();
        ~SystemGravity();

        SystemGravity(const SystemGravity &) = default;
        SystemGravity &operator=(const SystemGravity &) = default;


        void awake();
        void start();
        void update();
        void stop();
        void onTearDown();

    protected:
    private:
};

#endif /* !SystemGravity_HPP_ */

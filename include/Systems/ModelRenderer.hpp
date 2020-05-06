/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemModelRenderer
*/

#ifndef SystemModelRenderer_HPP_
#define SystemModelRenderer_HPP_

#include <iostream>
#include <memory>
#include <irrlicht.h>
#include <filesystem>
#include <limits.h>

#include "Exception.hpp"
#include "ECS/ASystem.hpp"
#include "Game.hpp"

#include "Components/ModelRenderer.hpp"
#include "Components/Window.hpp"
#include "Components/Transform.hpp"

class SystemModelRenderer : public is::ecs::ASystem {
    public:
        SystemModelRenderer();
        ~SystemModelRenderer();

        SystemModelRenderer(const SystemModelRenderer &) = default;
        SystemModelRenderer &operator=(const SystemModelRenderer &) = default;

        void awake();
        void start();
        void update();
        void stop();
        void onTearDown();

    protected:
    private:
};

#endif /* !SystemModelRenderer_HPP_ */

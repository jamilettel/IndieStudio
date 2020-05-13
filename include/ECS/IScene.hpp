/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Scene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "ECS/EntityManager.hpp"
#include "ECS/SystemManager.hpp"
#include "ECS/ComponentManager.hpp"

namespace is::ecs {

    class IScene {
        public:
            virtual ~IScene() = default;

            virtual void initSystems() = 0;
            virtual void initEntities() = 0;

            virtual void awake() = 0;
            virtual void start() = 0;
            virtual void update() = 0;
            virtual void stop() = 0;
            virtual void onTearDown() = 0;
    };

}

#endif /* !ISCENE_HPP_ */

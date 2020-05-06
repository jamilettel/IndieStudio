/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Scene
*/

#ifndef ASCENE_HPP_
#define ASCENE_HPP_

#include "ECS/IScene.hpp"

#include "ECS/EntityManager.hpp"
#include "ECS/SystemManager.hpp"
#include "ECS/ComponentManager.hpp"

namespace is::ecs {

    class AScene : public IScene {
        public:
            virtual ~AScene() = default;

            virtual void initSystems() = 0;

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
            EntityManager _entityManager;
            ComponentManager _componentManager;
            SystemManager _systemManager;
    };

}

#endif /* !ASCENE_HPP_ */

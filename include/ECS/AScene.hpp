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

            void initEntity(std::shared_ptr<Entity> &&entity);

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

        protected:
            std::shared_ptr<EntityManager> _entityManager;
            std::shared_ptr<ComponentManager> _componentManager;
            std::shared_ptr<SystemManager> _systemManager;
    };

}

#endif /* !ASCENE_HPP_ */

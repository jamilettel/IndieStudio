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
            AScene(Scenes sceneID);
            virtual ~AScene() = default;

            void initEntity(std::shared_ptr<Entity> &&entity);
            void initEntity(std::shared_ptr<Entity> &&entity, bool dontDestroyOnLoad);

            void initStaticEntities();

            void awake();
            void start();
            void update();
            void stop();
            void onTearDown();

            void deleteNonStaticEntites();

        protected:
            std::shared_ptr<EntityManager> _entityManager;
            static std::shared_ptr<EntityManager> _entitySaver;
            std::shared_ptr<ComponentManager> _componentManager;
            std::shared_ptr<SystemManager> _systemManager;
            Scenes _sceneID;
    };

}

#endif /* !ASCENE_HPP_ */

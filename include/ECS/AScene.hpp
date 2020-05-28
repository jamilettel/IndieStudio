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
            explicit AScene(Scenes sceneID);
            ~AScene() override = default;

            std::shared_ptr<Entity> &initEntity(std::shared_ptr<Entity> &&entity);
            std::shared_ptr<Entity> &initEntity(std::shared_ptr<Entity> &&entity, bool dontDestroyOnLoad);

            void initStaticEntities();

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;

            void deleteNonStaticEntities();

            static void saveEntity(std::shared_ptr<Entity> &e);

        protected:
            std::shared_ptr<EntityManager> _entityManager;
            static std::shared_ptr<EntityManager> _entitySaver;
            std::shared_ptr<ComponentManager> _componentManager;
            std::shared_ptr<SystemManager> _systemManager;
            Scenes _sceneID;
    };

}

#endif /* !ASCENE_HPP_ */

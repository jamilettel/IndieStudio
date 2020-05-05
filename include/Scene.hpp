/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "ECS/EntityManager.hpp"
#include "ECS/SystemManager.hpp"
#include "ECS/ComponentManager.hpp"

namespace is {

    class Scene {
        public:
            Scene();
            ~Scene();

        protected:
        private:
            ecs::EntityManager _entityManager;
            ecs::ComponentManager _componentManager;
            ecs::SystemManager _systemManager;
    };

}

#endif /* !SCENE_HPP_ */

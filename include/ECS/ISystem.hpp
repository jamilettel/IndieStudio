/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ISystem
*/

#ifndef ISYSTEM_HPP_
#define ISYSTEM_HPP_

#include "ECS/ComponentManager.hpp"

namespace is::ecs {

    class ISystem {
        public:
            virtual ~ISystem() = default;

            virtual void awake() = 0;
            virtual void start() = 0;
            virtual void update() = 0;
            virtual void stop() = 0;
            virtual void onTearDown() = 0;

            virtual void setComponentManager(std::shared_ptr<ComponentManager> _componentManager) = 0;

        protected:
        private:
    };

}

#endif /* !ISYSTEM_HPP_ */

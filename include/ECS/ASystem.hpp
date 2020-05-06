/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ASystem
*/

#ifndef ASystem_HPP_
#define ASystem_HPP_

#include "ECS/ISystem.hpp"

namespace is::ecs {

    class ASystem : public ISystem {
        public:
            virtual ~ASystem() = default;

            void setComponentManager(std::shared_ptr<ComponentManager> componentManager) final;

        protected:
            std::shared_ptr<ComponentManager> _componentManager;

    };

}

#endif /* !ASystem_HPP_ */

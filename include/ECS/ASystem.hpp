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
        void setEntityManager(std::shared_ptr<EntityManager> entityManager) final;

    protected:
        std::shared_ptr<ComponentManager> _componentManager;
        std::shared_ptr<EntityManager> _entityManager;

    };

}

#endif /* !ASystem_HPP_ */

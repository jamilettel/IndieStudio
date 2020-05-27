/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ASystem
*/

#ifndef ASYSTEM_HPP_
#define ASYSTEM_HPP_

#include "ECS/ISystem.hpp"

namespace is::ecs {

    class ASystem : public ISystem {
    public:
        ~ASystem() override = default;

        void setComponentManager(std::shared_ptr<ComponentManager> componentManager) final;
        void setEntityManager(std::shared_ptr<EntityManager> entityManager) final;
        std::shared_ptr<Entity> &initRuntimeEntity(std::shared_ptr<Entity> &&entity, bool keep = false) final;

    protected:
        std::shared_ptr<ComponentManager> _componentManager;
        std::shared_ptr<EntityManager> _entityManager;

    };

}

#endif /* !ASYSTEM_HPP_ */

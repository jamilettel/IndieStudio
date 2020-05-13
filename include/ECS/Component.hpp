/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include <memory>

namespace is::ecs {

    class Entity;

    class Component {
    public:
        explicit Component(std::shared_ptr<Entity> &e);
        virtual ~Component() = default;

        Component(const Component &) = delete;
        Component &operator=(const Component &) = delete;

        std::shared_ptr<is::ecs::Entity> getEntity();

        virtual void deleteComponent() = 0;

    protected:
        std::shared_ptr<Entity> _entity;

    };

}

#endif /* !COMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

namespace is::ecs {

    class Entity;

    class Component {
    public:
        explicit Component(Entity &e);
        virtual ~Component() = default;

        Component(const Component &) = delete;
        Component &operator=(const Component &) = delete;

        Entity &getEntity();

    protected:
        Entity &_entity;

    };

}

#endif /* !COMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Window
*/

#ifndef Window_HPP_
#define Window_HPP_

#include "ECS/Component.hpp"

class ComponentWindow : public is::ecs::Component {
    public:
        ComponentWindow(std::shared_ptr<is::ecs::Entity> &e);
        ~ComponentWindow() = default;

        ComponentWindow(const ComponentWindow &) = delete;
        ComponentWindow &operator=(const ComponentWindow &) = delete;

    protected:
    private:
};

#endif /* !Window_HPP_ */

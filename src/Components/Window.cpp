/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Window
*/

#include "Components/Window.hpp"

is::components::ComponentWindow::ComponentWindow(std::shared_ptr<is::ecs::Entity> &e,
                                                 const std::string &wn) :
Component(e)
{
    windowName = wn;
}

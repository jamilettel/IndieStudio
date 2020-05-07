/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRenderer
*/

#include "Components/ModelRenderer.hpp"

is::components::ComponentModelRenderer::ComponentModelRenderer(std::shared_ptr<is::ecs::Entity> &e,
                                                               const std::string &name,
                                                               const std::string &window) :
Component(e)
{
    fileName = name;
    windowName = window;
}

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRenderer
*/

#include "Components/ModelRenderer.hpp"

ComponentModelRenderer::ComponentModelRenderer(std::shared_ptr<is::ecs::Entity> &e, const std::string &name, int window) : Component(e)
{
    _name = name;
    _window = window;
}
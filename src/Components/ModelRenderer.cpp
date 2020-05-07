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

void is::components::ComponentModelRenderer::initModelRenderer(std::shared_ptr<is::components::ComponentWindow> ptr_window)
{
    node = ptr_window->scenemgr->addAnimatedMeshSceneNode(ptr_window->scenemgr->getMesh(fileName.c_str()));
    if (!node)
        throw new is::exceptions::Exception("ComponentModelRenderer", "Could not create node from model");
}
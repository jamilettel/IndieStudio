/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRenderer
*/

#include "Components/ModelRenderer.hpp"

is::components::ModelRendererComponent::ModelRendererComponent(std::shared_ptr<is::ecs::Entity> &e,
                                                               const std::string &name,
                                                               const std::string &window) :
Component(e)
{
    fileName = name;
    windowName = window;
}

void is::components::ModelRendererComponent::initModelRenderer(std::shared_ptr<is::components::WindowComponent> ptr_window)
{
    node = ptr_window->scenemgr->addAnimatedMeshSceneNode(ptr_window->scenemgr->getMesh(fileName.c_str()));
    if (!node)
        throw is::exceptions::Exception("ModelRendererComponent", "Could not create node from model");
}

irr::scene::IAnimatedMeshSceneNode *is::components::ModelRendererComponent::getElement() const
{
    return (node);
}

void is::components::ModelRendererComponent::deleteComponent()
{
    node->remove();
}

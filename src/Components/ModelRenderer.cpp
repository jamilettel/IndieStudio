/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRenderer
*/

#include "Components/ModelRenderer.hpp"
#include "Game.hpp"

using namespace is::ecs;
using namespace is::components;

ModelRendererComponent::ModelRendererComponent(std::shared_ptr<Entity> &e,
                                               std::string name,
                                               std::string window,
                                               std::string matName,
                                               bool shadow) :
Component(e), fileName(std::move(name)), materialName(std::move(matName)), windowName(std::move(window)), modelShadow(shadow)
{
}

void ModelRendererComponent::initModelRenderer(const std::shared_ptr<WindowComponent>& ptr_window)
{
    node = ptr_window->scenemgr->addAnimatedMeshSceneNode(static_cast<irr::scene::IAnimatedMesh *>(is::Game::getResource(fileName)));
    if (!node)
        throw is::exceptions::Exception("ModelRendererComponent", "Could not create node from model");
    if (!materialName.empty())
        node->setMaterialTexture(0, static_cast<irr::video::ITexture *>(is::Game::getResource(materialName)));
    if (modelShadow)
        node->addShadowVolumeSceneNode();
}

irr::scene::IAnimatedMeshSceneNode *ModelRendererComponent::getElement() const
{
    return (node);
}

void ModelRendererComponent::deleteComponent()
{
    if (!node)
        return;
    node->remove();
    node = nullptr;
}

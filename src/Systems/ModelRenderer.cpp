/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemModelRenderer
*/

#include "Systems/ModelRenderer.hpp"

using namespace irr;

SystemModelRenderer::SystemModelRenderer()
{
}

SystemModelRenderer::~SystemModelRenderer()
{
}

void SystemModelRenderer::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentModelRenderer).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentModelRenderer>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get ComponentModelRenderer pointer");
        try {
            auto window = _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code()).at(ptr->_window);
            auto ptr_window = std::dynamic_pointer_cast<ComponentWindow>(window);
            if (!ptr_window)
                throw new is::exceptions::Exception("SystemModelRenderer", "Could not get ComponentWindow pointer");
            ptr->node = ptr_window->scenemgr->addAnimatedMeshSceneNode(ptr_window->scenemgr->getMesh(ptr->_name.c_str()));
            if (!ptr->node)
                throw new is::exceptions::Exception("SystemModelRenderer", "Could not create node from model");
            ptr->node->setMaterialFlag(video::EMF_LIGHTING, false);
        } catch(const std::out_of_range &e) {
            std::cerr << "Impossible to get window with idx " << ptr->_window << std::endl;
        }
    }
}

void SystemModelRenderer::start()
{

}

void SystemModelRenderer::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentModelRenderer).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentModelRenderer>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get ComponentModelRenderer pointer");
        auto tr = ptr->getEntity()->getComponent<is::components::TransformComponent>();
        if (!tr)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get TransformComponent pointer");
        ptr->node->setPosition(tr->get()->position);
        ptr->node->setRotation(tr->get()->rotation);
        ptr->node->setScale(tr->get()->scale);
    }
}

void SystemModelRenderer::stop()
{

}

void SystemModelRenderer::onTearDown()
{

}


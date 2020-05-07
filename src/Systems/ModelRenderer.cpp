/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemModelRenderer
*/

#include "Systems/ModelRenderer.hpp"

using namespace irr;

void is::systems::SystemModelRenderer::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentModelRenderer).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentModelRenderer>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not get ComponentModelRenderer pointer");

        std::shared_ptr<is::components::ComponentWindow> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::ComponentWindow).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<is::components::ComponentWindow>(wc);
            if (!ptr_window)
                throw new is::exceptions::Exception("SystemModelRenderer", "Could not get ComponentWindow pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw new is::exceptions::Exception("SystemModelRenderer", "Could not found window");
        ptr->initModelRenderer(ptr_window);
    }
}

void is::systems::SystemModelRenderer::start()
{

}

void is::systems::SystemModelRenderer::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentModelRenderer).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentModelRenderer>(elem);
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

void is::systems::SystemModelRenderer::stop()
{

}

void is::systems::SystemModelRenderer::onTearDown()
{

}


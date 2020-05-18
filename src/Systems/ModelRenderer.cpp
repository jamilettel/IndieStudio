/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#include "Systems/ModelRenderer.hpp"

using namespace irr;

void is::systems::ModelRendererSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ModelRendererComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<is::components::ModelRendererComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("ModelRendererSystem", "Could not get ModelRendererComponent pointer");

        std::shared_ptr<is::components::WindowComponent> ptr_window;
        bool windowFound = false;
        for (auto &wc : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
            ptr_window = std::dynamic_pointer_cast<is::components::WindowComponent>(wc);
            if (!ptr_window)
                throw is::exceptions::Exception("ModelRendererSystem", "Could not get WindowComponent pointer");
            if (ptr_window->windowName == ptr->windowName) {
                windowFound = true;
                break;
            }
        }
        if (!windowFound)
            throw is::exceptions::Exception("ModelRendererSystem", "Could not find window");
        ptr->initModelRenderer(ptr_window);
    }
}

void is::systems::ModelRendererSystem::start()
{

}

void is::systems::ModelRendererSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ModelRendererComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ModelRendererComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("ModelRendererSystem", "Could not get ModelRendererComponent pointer");
        auto tr = ptr->getEntity()->getComponent<is::components::TransformComponent>();
        if (!tr)
            throw is::exceptions::Exception("ModelRendererSystem", "Could not get TransformComponent pointer");
        ptr->node->setPosition(tr->get()->position);
        ptr->node->setRotation(tr->get()->rotation);
        ptr->node->setScale(tr->get()->scale);
    }
}

void is::systems::ModelRendererSystem::stop()
{

}

void is::systems::ModelRendererSystem::onTearDown()
{

}


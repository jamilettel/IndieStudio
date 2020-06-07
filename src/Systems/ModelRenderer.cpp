/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRendererSystem
*/

#include "Systems/ModelRenderer.hpp"

using namespace irr;
using namespace is::components;

void is::systems::ModelRendererSystem::awake()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::ModelRendererComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<is::components::ModelRendererComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("ModelRendererSystem", "Could not get ModelRendererComponent pointer");

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("ModelRendererSystem", "Could not find window");

        auto window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        ptr->initModelRenderer(window);
    }
}

void is::systems::ModelRendererSystem::start()
{

}

void is::systems::ModelRendererSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::ModelRendererComponent).hash_code())) {
        const auto &ptr = static_cast<is::components::ModelRendererComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("ModelRendererSystem", "Could not get ModelRendererComponent pointer");
        const auto &tr = ptr->getEntity()->getComponent<is::components::TransformComponent>();
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


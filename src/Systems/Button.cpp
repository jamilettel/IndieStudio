/*
** EPITECH PROJECT, 2020
** Systems/ButtonSystem.cpp
** File description:
** 
*/

#include "Systems/Button.hpp"
#include "Components/Button.hpp"

#include <algorithm>
#include <iostream>
using namespace is::systems;
using namespace is::components;

void ButtonSystem::awake()
{
    auto &entity = initRuntimeEntity(prefabs::GlobalPrefabs::createClickSound(), false);

    _clickSound.emplace(**entity->getComponent<AudioComponent>());
    _clickSound->get().init();
    entity->setInit(true);

    for (auto &elem : _componentManager->getComponentsByType(typeid(ButtonComponent).hash_code())) {

        const auto &ptr = std::static_pointer_cast<ButtonComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("ButtonSystem", "Could not getButtonComponent pointer");

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("BombComponent", "Could not find window");

        auto window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        window->eventManager.addButton(ptr);

        if (elem->getEntity()->isInit())
            continue;

        ptr->init(window);
    }
}

void ButtonSystem::start()
{
}

void ButtonSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ButtonComponent).hash_code())) {
        const auto &ptr = static_cast<ButtonComponent*>(elem.get());
        if (ptr->isClicked()) {
            _clickSound->get().play();
            ptr->callCallback();
            ptr->setClicked(false);
        }
    }
}

void ButtonSystem::stop()
{
}

void ButtonSystem::onTearDown()
{
    for (auto &elem: _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        const auto &ptr = static_cast<WindowComponent*>(elem.get());
        ptr->eventManager.removeAllButtons();
    }
}

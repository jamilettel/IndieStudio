/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Cursor
*/

#include "Systems/Cursor.hpp"

using namespace is::ecs;
using namespace is::components;
using namespace is::systems;

void CursorSystem::awake()
{}

void CursorSystem::start()
{}

void CursorSystem::update()
{
    auto &list = _componentManager->getComponentsByType(typeid(CursorComponent).hash_code());

    for (auto &elem: list) {
        CursorComponent *cursor = static_cast<CursorComponent *>(elem.get());
        auto pos = cursor->getWindow().eventManager.getMousePosition();

        cursor->setPosition(pos.first, pos.second);
        cursor->getImage().setPosition(pos.first, pos.second);
    }
}

void CursorSystem::stop()
{
}

void CursorSystem::onTearDown()
{}

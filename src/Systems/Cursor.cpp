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
    const auto &list = _componentManager->getComponentsByType(typeid(CursorComponent).hash_code());

    for (const auto &elem: list) {
        auto cursor = static_cast<CursorComponent *>(elem.get());
        std::pair<float, float> pos;

        if (cursor->isMouseCursor) {
            pos = cursor->getWindow().eventManager.getMousePosition();
            cursor->setPosition(pos.first + 1, pos.second + 1);
        } else {
            pos.first = cursor->getPosition().X;
            pos.second = cursor->getPosition().Y;
        }

        cursor->getImage().setPosition(pos.first + 1, pos.second + 1);
        cursor->getImage().setVisible(cursor->visible);
    }
}

void CursorSystem::stop()
{
}

void CursorSystem::onTearDown()
{}

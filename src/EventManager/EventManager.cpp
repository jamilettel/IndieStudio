/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#include "EventManager/EventManager.hpp"

is::EventManager::EventManager()
{
    for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
        _keyState[i] = false;
}

is::EventManager::~EventManager()
= default;

bool is::EventManager::OnEvent(const SEvent &event)
{
    // Remember the mouse state
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        switch (event.MouseInput.Event) {
            case EMIE_LMOUSE_PRESSED_DOWN:
                _mouse.leftButtonDown = true;
                break;
            case EMIE_LMOUSE_LEFT_UP:
                _mouse.leftButtonDown = false;
                break;
            case EMIE_RMOUSE_PRESSED_DOWN:
                _mouse.rightButtonDown = true;
                break;
            case EMIE_RMOUSE_LEFT_UP:
                _mouse.rightButtonDown = false;
                break;
            case EMIE_MOUSE_MOVED:
                _mouse.position.X = event.MouseInput.X;
                _mouse.position.Y = event.MouseInput.Y;
                break;
            case EMIE_MOUSE_WHEEL:
                _mouse.wheelDelta = event.MouseInput.Wheel;
                break;
            default:
                break;
        }
    }
    // Remember whether each key is down or up
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
        _keyState[event.KeyInput.Key] = event.KeyInput.PressedDown;
    return false;
}

bool is::EventManager::IsKeyDown(enum EKEY_CODE keyCode) const
{
    return _keyState.at(keyCode);
}

std::pair<float, float> is::EventManager::getMousePosition() const
{
    return std::pair<float, float>(_mouse.position.X, _mouse.position.Y);
}

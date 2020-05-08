/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#include "EventManager/EventManager.hpp"
#include <iostream>

is::EventManager::EventManager()
{
    for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
        _keyState[i] = false;
}

is::EventManager::~EventManager()
= default;

bool is::EventManager::OnEvent(const SEvent &event)
{
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {

        // for (int i = 0; i < 6; i++) {
        //     std::cerr << i << ": " << event.JoystickEvent.Axis[i] << std::endl;
        // }

    }
    if (event.EventType == irr::EET_GUI_EVENT) {
        switch(event.GUIEvent.EventType) {
            case irr::gui::EGET_BUTTON_CLICKED:
                break;
            default:
                break;
        }
    }
    // Save the mouse state
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
            case EMIE_MMOUSE_PRESSED_DOWN:
                _mouse.middleButtonDown = true;
                break;
            case EMIE_MMOUSE_LEFT_UP:
                _mouse.middleButtonDown = false;
                break;
            case EMIE_MOUSE_MOVED:
                _mouse.position.X = event.MouseInput.X;
                _mouse.position.Y = event.MouseInput.Y;
                break;
            case EMIE_MOUSE_WHEEL:
                _mouse.wheelDelta += event.MouseInput.Wheel;
                break;
            default:
                break;
        }
    }
    // Check whether each key is down or up and run ft associated
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        _keyState[event.KeyInput.Key] = event.KeyInput.PressedDown;
        // run ft associated with key released
        if (!event.KeyInput.PressedDown) {
            if (_eventKeyReleased.find(event.KeyInput.Key) != _eventKeyReleased.end()) {
                _eventKeyReleased[event.KeyInput.Key]();
            }
        } else if (event.KeyInput.PressedDown) {
            std::pair<int, int> eventKey(0, event.KeyInput.Key);
            if (event.KeyInput.Control)
                eventKey.first = KEY_CONTROL;
            else if (event.KeyInput.Shift)
                eventKey.second = KEY_SHIFT;
            if (_eventKeyPressed.find(eventKey) != _eventKeyPressed.end())
                _eventKeyPressed[eventKey]();
        }
    }
    return false;
}

bool is::EventManager::IsKeyDown(enum EKEY_CODE keyCode) const
{
    return _keyState.at(keyCode);
}

void is::EventManager::setDeviceContext(IrrlichtDevice &device)
{
    _context.device = &device;
}

void is::EventManager::addEventKeyPressed(EKEY_CODE keyCtrl, EKEY_CODE keyCode, const std::function<void()> &ft)
{
    if (keyCtrl == KEY_CONTROL || keyCtrl == KEY_SHIFT || keyCtrl == 0) {
        if (_eventKeyPressed.find(std::pair<int, int>(keyCtrl, keyCode)) != _eventKeyPressed.end()) {
            //throw already exist
            return;
        }
        _eventKeyPressed[std::pair<int, int>(keyCtrl, keyCode)] = ft;
        return;
    }
    //throw invalid
}

void is::EventManager::addEventKeyPressed(EKEY_CODE keyCode, const std::function<void()> &ft)
{
    if (_eventKeyPressed.find(std::pair<int, int>(0, keyCode)) != _eventKeyPressed.end()) {
        //throw already exist
        return;
    }
    _eventKeyPressed[std::pair<int, int>(0, keyCode)] = ft;
}

void is::EventManager::removeEventKeyPressed(EKEY_CODE keyCtrl, EKEY_CODE keyCode)
{
    if (keyCtrl == KEY_CONTROL || keyCtrl == KEY_SHIFT) {
        if (_eventKeyPressed.find(std::pair<int, int>(keyCtrl, keyCode)) == _eventKeyPressed.end()) {
            //throw no exist exist
            return;
        }
        _eventKeyPressed.erase(std::pair<int, int>(keyCtrl, keyCode));
        return;
    }
    //throw invalid
}

void is::EventManager::removeEventKeyPressed(EKEY_CODE keyCode)
{
    if (_eventKeyPressed.find(std::pair<int, int>(0, keyCode)) == _eventKeyPressed.end()) {
        //throw no exist exist
        return;
    }
    _eventKeyPressed.erase(std::pair<int, int>(0, keyCode));
}

void is::EventManager::addEventKeyReleased(EKEY_CODE keyCode, const std::function<void()> &ft)
{
    if (_eventKeyReleased.find(keyCode) != _eventKeyReleased.end()) {
        //throw already exist
        return;
    }
    _eventKeyReleased[keyCode] = ft;
}

void is::EventManager::removeEventKeyReleased(EKEY_CODE keyCode)
{
    if (_eventKeyReleased.find(keyCode) == _eventKeyReleased.end()) {
        //throw no exist exist
        return;
    }
    _eventKeyReleased.erase(keyCode);
}

std::pair<float, float> is::EventManager::getMousePosition() const
{
    return std::pair<float, float>(_mouse.position.X, _mouse.position.Y);
}

bool is::EventManager::isRightPressed() const
{
    return _mouse.rightButtonDown;
}

bool is::EventManager::isMiddlePressed() const
{
    return _mouse.middleButtonDown;
}

bool is::EventManager::isLeftPressed() const
{
    return _mouse.leftButtonDown;
}

float is::EventManager::getMouseWheel() const
{
    return _mouse.wheelDelta;
}

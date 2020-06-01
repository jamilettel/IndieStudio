/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#include "EventManager/EventManager.hpp"
#include <iostream>
#include "Components/Button.hpp"

is::EventManager::EventManager() : _lastKeyPressed(EKEY_CODE::KEY_KEY_CODES_COUNT), _lastControlPressed(-9999)
{
    for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
        _keyState[i] = false;
}

is::EventManager::~EventManager() = default;

bool is::EventManager::OnEvent(const SEvent &event)
{
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
        memcpy(
            _joystickStates[event.JoystickEvent.Joystick].second,
            event.JoystickEvent.Axis,
            sizeof(s16[6])
            );
        _joystickStates[event.JoystickEvent.Joystick].first = event.JoystickEvent.ButtonStates;
    }
    if (event.EventType == irr::EET_GUI_EVENT) {
        switch(event.GUIEvent.EventType) {
            case irr::gui::EGET_BUTTON_CLICKED:
                checkButtonClicked(event.GUIEvent.Caller->getID());
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
        _lastKeyPressed = event.KeyInput.Key;
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

void is::EventManager::addButton(const std::shared_ptr<is::components::ButtonComponent>& toAdd)
{
    _context.button.push_back(toAdd);
}

void is::EventManager::removeButton(const std::shared_ptr<is::components::ButtonComponent>& toAdd)
{
    auto it = std::find(_context.button.begin(), _context.button.end(), toAdd);

    if (it != _context.button.end())
        _context.button.erase(it);
}

void is::EventManager::removeAllButtons()
{
    _context.button.clear();
}

void is::EventManager::checkButtonClicked(irr::s32 id)
{
    for (auto &it : _context.button) {
        if (it->getId() == id) {
            it->setClicked(true);
        }
    }
}

bool is::EventManager::isJoystickButtonPressed(u8 joystick, u32 button) const
{
    if (_joystickStates.count(joystick))
        return (_joystickStates.at(joystick).first & (1 << button)) != 0;
    return 0;
}

s16 is::EventManager::getAxisValue(u8 joystick, u32 axis) const
{
    if (_joystickStates.count(joystick))
        return _joystickStates.at(joystick).second[axis];
    return 0;
}

EKEY_CODE is::EventManager::getLastKeyPressed() const
{
    return _lastKeyPressed;
}

void is::EventManager::resetLastKeyPressed()
{
    _lastKeyPressed = EKEY_CODE::KEY_KEY_CODES_COUNT;
}

int is::EventManager::getLastControlPressed() const
{
    return _lastControlPressed;
}

void is::EventManager::resetLastControlPressed()
{
    _lastControlPressed = -9999;
}
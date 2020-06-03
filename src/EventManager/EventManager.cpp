/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** Event Manager
*/

#include "EventManager/EventManager.hpp"
#include "Components/Button.hpp"

using namespace is;

EventManager::EventManager() : _lastKeyPressed(irr::EKEY_CODE::KEY_KEY_CODES_COUNT), _lastControlPressed(-9999)
{
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
        _keyState[i] = false;
}

EventManager::~EventManager() = default;

bool EventManager::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
        memcpy(
            _joystickStates[event.JoystickEvent.Joystick].second,
            event.JoystickEvent.Axis,
            sizeof(irr::s16[6])
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
            case irr::EMIE_LMOUSE_PRESSED_DOWN:
                _mouse.leftButtonDown = true;
                break;
            case irr::EMIE_LMOUSE_LEFT_UP:
                _mouse.leftButtonDown = false;
                break;
            case irr::EMIE_RMOUSE_PRESSED_DOWN:
                _mouse.rightButtonDown = true;
                break;
            case irr::EMIE_RMOUSE_LEFT_UP:
                _mouse.rightButtonDown = false;
                break;
            case irr::EMIE_MMOUSE_PRESSED_DOWN:
                _mouse.middleButtonDown = true;
                break;
            case irr::EMIE_MMOUSE_LEFT_UP:
                _mouse.middleButtonDown = false;
                break;
            case irr::EMIE_MOUSE_MOVED:
                _mouse.position.X = event.MouseInput.X;
                _mouse.position.Y = event.MouseInput.Y;
                break;
            case irr::EMIE_MOUSE_WHEEL:
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
                eventKey.first = irr::KEY_CONTROL;
            else if (event.KeyInput.Shift)
                eventKey.second = irr::KEY_SHIFT;
            if (_eventKeyPressed.find(eventKey) != _eventKeyPressed.end())
                _eventKeyPressed[eventKey]();
        }
    }
    return false;
}

bool EventManager::IsKeyDown(enum irr::EKEY_CODE keyCode) const
{
    return _keyState.at(keyCode);
}

void EventManager::setDeviceContext(irr::IrrlichtDevice &device)
{
    _context.device = &device;
}

void EventManager::addEventKeyPressed(irr::EKEY_CODE keyCtrl, irr::EKEY_CODE keyCode, const std::function<void()> &ft)
{
    if (keyCtrl == irr::KEY_CONTROL || keyCtrl == irr::KEY_SHIFT || keyCtrl == 0) {
        if (_eventKeyPressed.find(std::pair<int, int>(keyCtrl, keyCode)) != _eventKeyPressed.end())
            throw is::exceptions::EventManagerException("Key already bound.");
        _eventKeyPressed[std::pair<int, int>(keyCtrl, keyCode)] = ft;
        return;
    }
    throw is::exceptions::EventManagerException("Key not found.");
}

void EventManager::addEventKeyPressed(irr::EKEY_CODE keyCode, const std::function<void()> &ft)
{
    if (_eventKeyPressed.find(std::pair<int, int>(0, keyCode)) != _eventKeyPressed.end())
        throw is::exceptions::EventManagerException("Key already bound.");
    _eventKeyPressed[std::pair<int, int>(0, keyCode)] = ft;
}

void EventManager::removeEventKeyPressed(irr::EKEY_CODE keyCtrl, irr::EKEY_CODE keyCode)
{
    if (keyCtrl == irr::KEY_CONTROL || keyCtrl == irr::KEY_SHIFT) {
        if (_eventKeyPressed.find(std::pair<int, int>(keyCtrl, keyCode)) == _eventKeyPressed.end())
            throw is::exceptions::EventManagerException("Event not found.");
        _eventKeyPressed.erase(std::pair<int, int>(keyCtrl, keyCode));
        return;
    }
    throw is::exceptions::EventManagerException("Key not found.");
}

void EventManager::removeEventKeyPressed(irr::EKEY_CODE keyCode)
{
    if (_eventKeyPressed.find(std::pair<int, int>(0, keyCode)) == _eventKeyPressed.end())
        throw is::exceptions::EventManagerException("Key not found.");
    _eventKeyPressed.erase(std::pair<int, int>(0, keyCode));
}

void EventManager::addEventKeyReleased(irr::EKEY_CODE keyCode, const std::function<void()> &ft)
{
    if (_eventKeyReleased.find(keyCode) != _eventKeyReleased.end())
        throw is::exceptions::EventManagerException("Key already bound.");
    _eventKeyReleased[keyCode] = ft;
}

void EventManager::removeEventKeyReleased(irr::EKEY_CODE keyCode)
{
    if (_eventKeyReleased.find(keyCode) == _eventKeyReleased.end())
        throw is::exceptions::EventManagerException("Key to remove not found.");
    _eventKeyReleased.erase(keyCode);
}

std::pair<float, float> EventManager::getMousePosition() const
{
    return std::pair<float, float>(_mouse.position.X, _mouse.position.Y);
}

bool EventManager::isRightPressed() const
{
    return _mouse.rightButtonDown;
}

bool EventManager::isMiddlePressed() const
{
    return _mouse.middleButtonDown;
}

bool EventManager::isLeftPressed() const
{
    return _mouse.leftButtonDown;
}

float EventManager::getMouseWheel() const
{
    return _mouse.wheelDelta;
}

void EventManager::addButton(const std::shared_ptr<components::ButtonComponent>& toAdd)
{
    _context.button.push_back(toAdd);
}

void EventManager::removeButton(const std::shared_ptr<components::ButtonComponent>& toAdd)
{
    auto it = std::find(_context.button.begin(), _context.button.end(), toAdd);

    if (it != _context.button.end())
        _context.button.erase(it);
}

void EventManager::removeAllButtons()
{
    _context.button.clear();
}

void EventManager::checkButtonClicked(irr::s32 id)
{
    for (auto &it : _context.button) {
        if (it->getId() == id) {
            it->setClicked(true);
        }
    }
}

bool EventManager::isJoystickButtonPressed(irr::u8 joystick, irr::u32 button) const
{
    if (_joystickStates.count(joystick))
        return (_joystickStates.at(joystick).first & (1 << button)) != 0;
    return 0;
}

irr::s16 EventManager::getAxisValue(irr::u8 joystick, irr::u32 axis) const
{
    if (_joystickStates.count(joystick))
        return _joystickStates.at(joystick).second[axis];
    return 0;
}

irr::EKEY_CODE EventManager::getLastKeyPressed() const
{
    return _lastKeyPressed;
}

void EventManager::resetLastKeyPressed()
{
    _lastKeyPressed = irr::EKEY_CODE::KEY_KEY_CODES_COUNT;
}

int EventManager::getLastControlPressed() const
{
    return _lastControlPressed;
}

void EventManager::resetLastControlPressed()
{
    _lastControlPressed = -9999;
}

bool EventManager::IsJoystickButtonDown(irr::u8 id, int key) const
{
    return false;
}

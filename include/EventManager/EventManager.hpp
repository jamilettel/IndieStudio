/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#ifndef BOMBERMAN_EVENTMANAGER_HPP
#define BOMBERMAN_EVENTMANAGER_HPP

#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <vector>
#include <irrlicht.h>
#include <map>
#include <functional>
#include <memory>
#include "ECS/Component.hpp"

using namespace irr;

namespace is::components
{
    class ButtonComponent;
}

namespace is
{
    typedef struct SMouseState {
        core::position2di position;
        bool leftButtonDown;
        bool middleButtonDown;
        bool rightButtonDown;
        float wheelDelta;
        SMouseState() : leftButtonDown(false), middleButtonDown(false), rightButtonDown(false),
        wheelDelta(0.0) {}
    } mouseState;

    typedef struct SAppContext {
        IrrlichtDevice *device;
        s32 counter;
        std::vector<std::shared_ptr<is::components::ButtonComponent>> button;
        SAppContext() : device(nullptr), counter(0) {}
    } appContext;

    class EventManager : public IEventReceiver {
        public:
            EventManager();
            ~EventManager() override;

            /* IMPORTANT, THEY SHOULDN'T BE CHANGED */
            bool OnEvent(const SEvent &event) override;
            [[nodiscard]] bool IsKeyDown(EKEY_CODE keyCode) const;
            [[nodiscard]] bool IsJoystickButtonDown(u8 id, int key) const;

            /* CONTEXT METHODS */
            void setDeviceContext(IrrlichtDevice &device);

            /* OTHER METHODS */
            [[nodiscard]] std::pair<float, float> getMousePosition() const;
            [[nodiscard]] bool isRightPressed() const;
            [[nodiscard]] bool isMiddlePressed() const;
            [[nodiscard]] bool isLeftPressed() const;
            [[nodiscard]] float getMouseWheel() const;
            [[nodiscard]] EKEY_CODE getLastKeyPressed() const;
            void resetLastKeyPressed();
            [[nodiscard]] int getLastControlPressed() const;
            void resetLastControlPressed();

            void addEventKeyPressed(EKEY_CODE keyCtrl, EKEY_CODE keyCode, const std::function<void()> &ft);
            void addEventKeyPressed(EKEY_CODE keyCode, const std::function<void()> &ft);
            void removeEventKeyPressed(EKEY_CODE keyCtrl, EKEY_CODE keyCode);
            void removeEventKeyPressed(EKEY_CODE keyCode);

            void addEventKeyReleased(EKEY_CODE keyCode, const std::function<void()> &ft);
            void removeEventKeyReleased(EKEY_CODE keyCode);

            void addButton(const std::shared_ptr<is::components::ButtonComponent>&);
            void checkButtonClicked(irr::s32 id);

            void removeButton(const std::shared_ptr<is::components::ButtonComponent>&);
            void removeAllButtons();

            [[nodiscard]] bool isJoystickButtonPressed(u8 joystick, u32 button) const;
            [[nodiscard]] s16 getAxisValue(u8 joystick, u32 axis) const;
            bool isJoystickEvent() const;
            void resetJoystickEvent();

        private:
            appContext _context;

            std::map<int, bool> _keyState;
            std::map<u8, std::pair<u32, s16[6]>> _joystickStates;
            mouseState _mouse;

            std::map<std::pair<int, int>, std::function<void()>> _eventKeyPressed;
            std::map<int, std::function<void()>> _eventKeyReleased;
            EKEY_CODE _lastKeyPressed;
            int _lastControlPressed;
            bool _eventController;
    };
}

#endif //BOMBERMAN_EVENTMANAGER_HPP

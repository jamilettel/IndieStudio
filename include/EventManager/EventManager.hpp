/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** TODO: add description
*/

#ifndef BOMBERMAN_EVENTMANAGER_HPP
#define BOMBERMAN_EVENTMANAGER_HPP

#include <irrlicht.h>
#include <functional>
#include <memory>
#include <vector>
#include <map>
#include "ECS/Component.hpp"

namespace is::components
{
    class ButtonComponent;
}

namespace is
{
    typedef struct SMouseState {
        irr::core::position2di position;
        bool leftButtonDown;
        bool middleButtonDown;
        bool rightButtonDown;
        float wheelDelta;
        SMouseState() : leftButtonDown(false), middleButtonDown(false), rightButtonDown(false),
        wheelDelta(0.0) {}
    } mouseState;

    typedef struct SAppContext {
        irr::IrrlichtDevice *device;
        irr::s32 counter;
        std::vector<std::shared_ptr<is::components::ButtonComponent>> button;
        SAppContext() : device(nullptr), counter(0) {}
    } appContext;

class EventManager : public irr::IEventReceiver {
        public:
            EventManager();
            ~EventManager() override;

            /* IMPORTANT, THEY SHOULDN'T BE CHANGED */
            bool OnEvent(const irr::SEvent &event) override;
            [[nodiscard]] bool IsKeyDown(irr::EKEY_CODE keyCode) const;
            [[nodiscard]] bool IsJoystickButtonDown(irr::u8 id, int key) const;

            /* CONTEXT METHODS */
            void setDeviceContext(irr::IrrlichtDevice &device);

            /* OTHER METHODS */
            [[nodiscard]] std::pair<float, float> getMousePosition() const;
            [[nodiscard]] bool isRightPressed() const;
            [[nodiscard]] bool isMiddlePressed() const;
            [[nodiscard]] bool isLeftPressed() const;
            [[nodiscard]] float getMouseWheel() const;
            [[nodiscard]] irr::EKEY_CODE getLastKeyPressed() const;
            void resetLastKeyPressed();
            [[nodiscard]] int getLastControlPressed() const;
            void resetLastControlPressed();

            void addEventKeyPressed(irr::EKEY_CODE keyCtrl, irr::EKEY_CODE keyCode, const std::function<void()> &ft);
            void addEventKeyPressed(irr::EKEY_CODE keyCode, const std::function<void()> &ft);
            void removeEventKeyPressed(irr::EKEY_CODE keyCtrl, irr::EKEY_CODE keyCode);
            void removeEventKeyPressed(irr::EKEY_CODE keyCode);

            void addEventKeyReleased(irr::EKEY_CODE keyCode, const std::function<void()> &ft);
            void removeEventKeyReleased(irr::EKEY_CODE keyCode);

            void addButton(const std::shared_ptr<is::components::ButtonComponent>&);
            void checkButtonClicked(irr::s32 id);

            void removeButton(const std::shared_ptr<is::components::ButtonComponent>&);
            void removeAllButtons();

            [[nodiscard]] bool isJoystickButtonPressed(irr::u8 joystick, irr::u32 button) const;
            [[nodiscard]] irr::s16 getAxisValue(irr::u8 joystick, irr::u32 axis) const;

        private:
            appContext _context;

            std::map<int, bool> _keyState;
            std::map<irr::u8, std::pair<irr::u32, irr::s16[6]>> _joystickStates;
            mouseState _mouse;

            std::map<std::pair<int, int>, std::function<void()>> _eventKeyPressed;
            std::map<int, std::function<void()>> _eventKeyReleased;
            irr::EKEY_CODE _lastKeyPressed;
            int _lastControlPressed;
    };
}

#endif //BOMBERMAN_EVENTMANAGER_HPP

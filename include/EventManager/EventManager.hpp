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

#include <irrlicht.h>
#include <driverChoice.h>
#include <map>

using namespace irr;

namespace is
{
    typedef struct SMouseState
    {
        core::position2di position;
        bool leftButtonDown;
        bool rightButtonDown;
        float wheelDelta;
        SMouseState() : leftButtonDown(false), rightButtonDown(false),
        wheelDelta(0.0) {}
    } mouseState;

    class EventManager : public IEventReceiver
    {
        public:
            EventManager();
            ~EventManager() override;

            /* IMPORTANT, THEY SHOULDN'T BE CHANGED */
            bool OnEvent(const SEvent &event) override;
            [[nodiscard]] bool IsKeyDown(EKEY_CODE keyCode) const;

            /* OTHER METHODS */
            std::pair<float, float> getMousePosition() const;

        private:
            std::map<int, bool> _keyState;
            mouseState _mouse;
    };
}

#endif //BOMBERMAN_EVENTMANAGER_HPP

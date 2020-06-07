/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WindowComponent
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <irrlicht.h>
#include <string>
#include "ECS/Component.hpp"
#include "EventManager/EventManager.hpp"

namespace is::components {

    class WindowComponent : public is::ecs::Component {
    public:
        explicit WindowComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            const std::string &windowName = "MainWindow",
            irr::core::dimension2d<irr::u32> ws = irr::core::dimension2d<irr::u32>(1920, 1080),
            bool fs = false
            );
        ~WindowComponent() override = default;

        WindowComponent(const WindowComponent &) = delete;
        WindowComponent &operator=(const WindowComponent &) = delete;

        void deleteComponent() override;

        irr::IrrlichtDevice *device{};
        irr::video::IVideoDriver *driver{};
        irr::scene::ISceneManager *scenemgr{};
        irr::gui::IGUIEnvironment *canvas{};

        is::EventManager eventManager;

        std::string windowName;
        irr::core::dimension2d<irr::u32> windowSize;
        bool fullscreen;

        irr::core::array<irr::SJoystickInfo> joysticks;

        static std::map<std::string, std::pair<int, int>> _windowsDimensions;
        static int _width;
        static int _height;

    };
}

#endif /* !Window_HPP_ */

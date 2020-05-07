/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Window
*/

#ifndef Window_HPP_
#define Window_HPP_

#include <irrlicht.h>
#include <string>

#include "ECS/Component.hpp"

#include "EventManager/EventManager.hpp"

namespace is::components {

    class WindowComponent : public is::ecs::Component {
    public:
        WindowComponent(std::shared_ptr<is::ecs::Entity> &e,
                        const std::string &windowName = "MainWindow",
                        irr::core::dimension2d<u32> ws = irr::core::dimension2d<u32>(1600, 900),
                        bool fs = false);
        ~WindowComponent() = default;

        WindowComponent(const WindowComponent &) = delete;
        WindowComponent &operator=(const WindowComponent &) = delete;

        void deleteComponent();

        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver* driver;
        irr::scene::ISceneManager* scenemgr;

        is::EventManager eventManager;
    
        std::string windowName;
        irr::core::dimension2d<u32> windowSize;
        bool fullscreen;

    };

}

#endif /* !Window_HPP_ */

/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** GUIElement
*/

#ifndef GUIELEMENTCOMPONENT_HPP_
#define GUIELEMENTCOMPONENT_HPP_

#include "ECS/Component.hpp"
#include "Components/Window.hpp"

namespace is::components {

    class GUIElementComponent: public is::ecs::Component {
        public:
            explicit GUIElementComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~GUIElementComponent() override = default;

            GUIElementComponent(const GUIElementComponent &) = delete;
            GUIElementComponent &operator=(const GUIElementComponent &) = delete;

            virtual void bringToFront() = 0;

            virtual void init(std::shared_ptr<is::components::WindowComponent> &ptr_window) = 0;

        public:
            int layer = 0;

        protected:
            std::shared_ptr<WindowComponent> _window;
    };

}

#endif /* !GUIELEMENTCOMPONENT_HPP_ */

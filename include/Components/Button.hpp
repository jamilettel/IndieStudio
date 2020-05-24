/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef BUTTONCOMPONENT_HPP_
#define BUTTONCOMPONENT_HPP_

#include <vector>
#include "ECS/Component.hpp"
#include <memory>
#include <irrlicht.h>
#include "Components/Window.hpp"
#include "Exception.hpp"
#include "Components/GUIElement.hpp"

namespace is::components {

    class ButtonComponent: public GUIElementComponent {
        public:
            ButtonComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                const std::string &text,
                const std::string &wn,
                irr::s32 x,
                irr::s32 y,
                irr::s32 width,
                irr::s32 height,
                std::function<void()> ft,
                bool visible
            );
            ButtonComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                const std::string &text,
                const std::string &wn,
                irr::s32 x,
                irr::s32 y,
                irr::s32 width,
                irr::s32 height,
                std::function<void()> ft,
                bool visible,
                const std::string &image,
                const std::string &pressed
            );
            ButtonComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                const std::string &text,
                const std::string &wn,
                irr::s32 x,
                irr::s32 y,
                irr::s32 width,
                irr::s32 height,
                std::function<void()> ft,
                bool visible,
                const std::string &image,
                const std::string &pressed,
                const std::string &font
            );
            ~ButtonComponent() override = default;

            ButtonComponent(const ButtonComponent &) = delete;
            ButtonComponent &operator=(const ButtonComponent &) = delete;

            void init(std::shared_ptr<is::components::WindowComponent> &ptr_window) override;
            void deleteComponent() override;
            [[nodiscard]] irr::s32 getId() const;

            [[nodiscard]] bool isClicked() const;
            void setClicked(bool);

            void setCallback(std::function<void()> ft);
            void callCallback() const;

            void bringToFront() override;
            void setVisible(bool visible);

            std::string windowName;

        private:
            const std::string _image;
            const std::string _pressed;
            const std::string _font;
            std::string _text;
            irr::core::rect<irr::s32> _dimension;
            irr::gui::IGUIButton *element{};
            bool _clicked;
            bool _visible;
            std::function<void()> _ft;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

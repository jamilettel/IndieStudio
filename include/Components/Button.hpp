/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef BUTTONCOMPONENT_HPP_
#define BUTTONCOMPONENT_HPP_

#include <irrlicht.h>

#include "Components/GUIElement.hpp"
#include "ECS/Component.hpp"
#include "Exception.hpp"

namespace is::components {

    class ButtonComponent: public GUIElementComponent {
        public:
            ButtonComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                std::string text,
                std::string wn,
                irr::s32 x,
                irr::s32 y,
                irr::s32 width,
                irr::s32 height,
                std::function<void()> ft,
                bool visible
            );
            ButtonComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                std::string text,
                std::string wn,
                irr::s32 x,
                irr::s32 y,
                irr::s32 width,
                irr::s32 height,
                std::function<void()> ft,
                bool visible,
                std::string image,
                std::string pressed
            );
            ButtonComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                std::string text,
                std::string wn,
                irr::s32 x,
                irr::s32 y,
                irr::s32 width,
                irr::s32 height,
                std::function<void()> ft,
                bool visible,
                std::string image,
                std::string pressed,
                std::string font
            );
            ~ButtonComponent() override = default;

            ButtonComponent(const ButtonComponent &) = delete;
            ButtonComponent &operator=(const ButtonComponent &) = delete;

            void init(std::shared_ptr<is::components::WindowComponent> &ptrWindow) override;
            void deleteComponent() override;
            [[nodiscard]] irr::s32 getId() const;

            [[nodiscard]] bool isClicked() const;
            void setClicked(bool);

            void setCallback(std::function<void()> ft);
            void callCallback(int cursorId = -1);

            void bringToFront() override;
            void setVisible(bool visible);

            [[nodiscard]] bool isDisabled() const noexcept;
            void setDisabled(bool disabled) noexcept;

            std::string windowName;

            [[nodiscard]] bool contains(const irr::core::vector2df &pos) const;
            [[nodiscard]] int getCallerId() const;

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
            int _disabled = 0;
           int _callerId = -1;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

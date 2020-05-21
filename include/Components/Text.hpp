/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef TEXTCOMPONENT_HPP_
#define TEXTCOMPONENT_HPP_

#include <vector>
#include "ECS/Component.hpp"
#include <memory>
#include <irrlicht.h>
#include "Components/Window.hpp"
#include "Exception.hpp"
#include "IDGenerator.hpp"
#include "Components/GUIElement.hpp"

namespace is::components {
    class TextComponent: public GUIElementComponent {
    public:
        TextComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            std::string text,
            std::string wn,
            irr::s32 x,
            irr::s32 y,
            irr::s32 width,
            irr::s32 height,
            bool drawBorder,
            bool dynamic);

        TextComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            std::string text,
            std::string wn,
            irr::s32 x,
            irr::s32 y,
            irr::s32 width,
            irr::s32 height,
            bool drawBorder,
            bool dynamic,
            std::string font);

        TextComponent(
        std::shared_ptr<is::ecs::Entity> &e,
        std::string text,
        std::string wn,
        irr::s32 x,
        irr::s32 y,
        irr::s32 width,
        irr::s32 height,
        bool drawBorder,
        bool dynamic,
        std::string font,
        irr::video::SColor color);

        ~TextComponent() override = default;

        TextComponent(const TextComponent &) = delete;
        TextComponent &operator=(const TextComponent &) = delete;

        void init(std::shared_ptr<is::components::WindowComponent>& ptr_window) override;
        void bringToFront() override;
        void deleteComponent() override;

        void updateText();
        [[nodiscard]] std::string getText() const;
        void setText(const std::string &string);

        void setVisible(bool visible);

        std::string windowName;

    private:
        irr::gui::IGUIStaticText *element{};
        irr::core::rect<irr::s32> _dimension;
        std::string _text;
        std::string _font;
        irr::video::SColor _color;
        bool _drawBorder;
        bool _dynamic;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef TEXTCOMPONENT_HPP_
#define TEXTCOMPONENT_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"
#include "Exception.hpp"
#include "Components/GUIElement.hpp"
#include "IDGenerator.hpp"

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
            bool dynamic,
            bool visible = true);

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
            bool visible = true);

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
            irr::video::SColor color,
            bool visible = true);

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
        void move(const irr::core::vector2di &pos) noexcept;

        std::string windowName;

    private:
        irr::gui::IGUIStaticText *element{};
        irr::core::rect<irr::s32> _dimension;
        std::string _text;
        std::string _font;
        irr::video::SColor _color;
        bool _drawBorder;
        bool _dynamic;
        bool _visible;
        bool _dimensionChange = false;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

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

namespace is::components {

    class TextComponent: public is::ecs::Component {

    public:
        TextComponent(std::shared_ptr<is::ecs::Entity> &e, std::string text, std::string wn,
                irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height,
                bool drawBorder, bool dynamic);
        
        TextComponent(std::shared_ptr<is::ecs::Entity> &e, std::string text, std::string wn,
                irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height,
                bool drawBorder, bool dynamic, std::string font);

        TextComponent(std::shared_ptr<is::ecs::Entity> &e, std::string text, std::string wn,
                irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height,
                bool drawBorder, bool dynamic, std::string font, irr::video::SColor color);
        ~TextComponent() override = default;

        TextComponent(const TextComponent &) = delete;
        TextComponent &operator=(const TextComponent &) = delete;

        void init(const std::shared_ptr<is::components::WindowComponent>& ptr_window);
        
        void updateText();
        [[nodiscard]] std::string getText() const;
        void setText(const std::string &string);
        

        void deleteComponent() override;
        
        std::string windowName;
    private:
        std::string _text;
        irr::core::rect<irr::s32> _dimension;
        irr::gui::IGUIStaticText *element{};
        bool _drawBorder;
        std::string _font;
        bool _dynamic;
        irr::video::SColor _color;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

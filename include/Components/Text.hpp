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

namespace is::components {

    class TextComponent: public is::ecs::Component {

    public:
        TextComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &text, const std::string &wn,
                irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height,
                bool drawBorder);
        
        TextComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &text, const std::string &wn,
                irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height,
                bool drawBorder, const std::string &font);
        ~TextComponent() = default;

        TextComponent(const TextComponent &) = delete;
        TextComponent &operator=(const TextComponent &) = delete;

        void init(std::shared_ptr<is::components::WindowComponent> ptr_window);
        void deleteComponent();
        
        std::string windowName;
    private:
        std::string _text;
        irr::core::rect<irr::s32> _dimension;
        irr::gui::IGUIStaticText *element;
        bool _drawBorder;
        std::string _font;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

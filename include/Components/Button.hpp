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

namespace is::components {

    class ButtonComponent: public is::ecs::Component {

    public:
        ButtonComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &text, const std::string &wn,
                irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height,
                void (*fct)());
        ~ButtonComponent() = default;

        ButtonComponent(const ButtonComponent &) = delete;
        ButtonComponent &operator=(const ButtonComponent &) = delete;

        void init(std::shared_ptr<is::components::WindowComponent> ptr_window);
        void deleteComponent();
        void (*fctButton)();
        bool isClicked() const;
        void setClicked(bool);
        irr::s32 getId() const;

        std::string windowName;
    private:
        bool _clicked;
        std::string _text;
        irr::core::rect<irr::s32> _dimension;
        irr::gui::IGUIButton *element;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

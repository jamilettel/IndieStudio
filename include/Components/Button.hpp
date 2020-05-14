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
            ButtonComponent(std::shared_ptr<is::ecs::Entity> &e, std::string text, std::string wn,
                    irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height, std::function<void()> ft);
            ButtonComponent(std::shared_ptr<is::ecs::Entity> &e, std::string text, std::string wn,
                    irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height,
                    std::function<void()> ft, std::string image, std::string pressed);
            ButtonComponent(std::shared_ptr<is::ecs::Entity> &e, std::string text, std::string wn,
                    irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height,
                    std::function<void()> ft, std::string image, std::string pressed,
                    std::string font);
            ~ButtonComponent() override = default;

            ButtonComponent(const ButtonComponent &) = delete;
            ButtonComponent &operator=(const ButtonComponent &) = delete;

            void init(std::shared_ptr<is::components::WindowComponent> &ptr_window);
            void deleteComponent() override;
            std::function<void()> _ft;
            [[nodiscard]] bool isClicked() const;
            void setClicked(bool);
            [[nodiscard]] irr::s32 getId() const;

            std::string windowName;
        private:
            bool _clicked;
            std::string _text;
            irr::core::rect<irr::s32> _dimension;
            irr::gui::IGUIButton *element{};
            const std::string _image;
            const std::string _pressed;
            const std::string _font;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

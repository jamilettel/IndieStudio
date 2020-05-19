/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef IMAGECOMPONENT_HPP_
#define IMAGECOMPONENT_HPP_

#include <vector>
#include "ECS/Component.hpp"
#include <memory>
#include <irrlicht.h>
#include "Components/Window.hpp"
#include "Exception.hpp"
#include "Components/GUIElement.hpp"

namespace is::components {

    class ImageComponent: public GUIElementComponent {
    public:
        ImageComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            std::string filename,
            std::string wn,
            int x,
            int y,
            bool scale = false
            );
        ~ImageComponent() override = default;

        ImageComponent(const ImageComponent &) = delete;
        ImageComponent &operator=(const ImageComponent &) = delete;

        void init(std::shared_ptr<is::components::WindowComponent> &ptr_window) override;
        void setPosition(float x, float y);
        void deleteComponent() override;

        void bringToFront() override;

        std::string windowName;

    private:
        irr::core::vector2d<int> _dimension;
        std::string _filename;
        irr::gui::IGUIImage *element{};
        bool _scale;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

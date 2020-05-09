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

namespace is::components {

    class ImageComponent: public is::ecs::Component {

    public:
        ImageComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, const std::string &wn,
                int x, int y);
        ~ImageComponent() = default;

        ImageComponent(const ImageComponent &) = delete;
        ImageComponent &operator=(const ImageComponent &) = delete;

        void init(std::shared_ptr<is::components::WindowComponent> ptr_window);
        void deleteComponent();
       
        std::string windowName;
    private:
        irr::core::vector2d<int> _dimension;
        std::string _filename;
        irr::gui::IGUIImage *element;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

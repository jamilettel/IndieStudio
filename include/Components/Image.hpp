/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef IMAGECOMPONENT_HPP_
#define IMAGECOMPONENT_HPP_

#include "ECS/Component.hpp"
#include "Exception.hpp"
#include "Components/Window.hpp"
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
            bool scale = false,
            bool visible = true
            );
        ~ImageComponent() override = default;

        ImageComponent(const ImageComponent &) = delete;
        ImageComponent &operator=(const ImageComponent &) = delete;

        void init(std::shared_ptr<is::components::WindowComponent> &ptr_window) override;
        void deleteComponent() override;
        void bringToFront() override;

        void setPosition(float x, float y);
        void setVisible(bool visible);

        [[nodiscard]] const irr::core::vector2d<int> &getPosition() const;

        void setImage(irr::video::ITexture *image);

        std::string windowName;

    private:
        irr::gui::IGUIImage *element{};
        irr::core::vector2d<int> _dimension;
        std::string _filename;
        bool _scale;
        bool _visible;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

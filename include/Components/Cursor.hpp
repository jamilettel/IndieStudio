
/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Cursor
*/

#ifndef CURSORCOMPONENT_HPP_
#define CURSORCOMPONENT_HPP_

#include "Components/Image.hpp"
#include "Components/Window.hpp"

namespace is::components {

    class CursorComponent: public is::ecs::Component {
    public:
        CursorComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            ImageComponent &cursorImage,
            WindowComponent &window
            );
        ~CursorComponent() = default;

        CursorComponent(const CursorComponent &) = delete;
        CursorComponent &operator=(const CursorComponent &) = delete;

        void deleteComponent() override;

        void setPosition(float x, float y);
        void move(float x, float y);

        [[nodiscard]] const irr::core::vector2df &getPosition() const noexcept;

        [[nodiscard]] ImageComponent &getImage() const noexcept;

    private:
        ImageComponent &_cursorImage;
        WindowComponent &_window;
        irr::core::vector2df _pos;

    };

}

#endif /* !CURSORCOMPONENT_HPP_ */

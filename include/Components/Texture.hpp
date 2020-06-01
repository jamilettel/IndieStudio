/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Texture
*/

#ifndef TEXTURE_HPP_
#define TEXTURE_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"
#include "Components/Window.hpp"

namespace is::components
{
    class TextureComponent: public is::ecs::Component {
        public:
            TextureComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                const std::string &filename,
                const std::string &windowName,
                const irr::core::vector2df &pos,
                const irr::core::vector2df &size,
                bool visible = true
            );

            ~TextureComponent() override = default;

            TextureComponent(const TextureComponent &) = delete;
            TextureComponent &operator=(const TextureComponent &) = delete;

            void deleteComponent() override;

            void init(std::shared_ptr<is::components::WindowComponent> &ptrWindow);

            void setPosition(const irr::core::vector2df &position) noexcept;

            [[nodiscard]] const irr::core::vector2df &getPosition() const noexcept;
            [[nodiscard]] const irr::core::vector2df &getSize() const noexcept;
            [[nodiscard]] irr::video::ITexture *getNode() const noexcept;
            [[nodiscard]] bool isVisible() const noexcept;
            void setVisible(bool visible) noexcept;

            std::string filename;
            std::string windowName;
       private:
            irr::video::ITexture *_node;
            irr::core::vector2df _pos;
            irr::core::vector2df _size;
            bool _visible;
    };

}

#endif /* !TEXTURE_HPP_ */

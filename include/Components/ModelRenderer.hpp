/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRenderer
*/

#ifndef ModelRenderer_HPP_
#define ModelRenderer_HPP_

#include <irrlicht.h>
#include <string>

#include "ECS/Component.hpp"
#include "Components/Window.hpp"

#include "Exception.hpp"
namespace is::components {
    class ModelRendererComponent : public is::ecs::Component {
        public:
            ModelRendererComponent(std::shared_ptr<is::ecs::Entity> &e,
                                   const std::string &name,
                                   const std::string &wn);
            ~ModelRendererComponent() override = default;

            ModelRendererComponent(const ModelRendererComponent &) = delete;
            ModelRendererComponent &operator=(const ModelRendererComponent &) = delete;

            void deleteComponent() override;

            void initModelRenderer(std::shared_ptr<is::components::WindowComponent> ptr_window);

            std::string fileName;
            std::string windowName;
            irr::scene::IAnimatedMeshSceneNode *node{};
    };

}

#endif /* !ModelRenderer_HPP_ */

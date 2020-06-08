/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ModelRenderer
*/

#ifndef MODELRENDERER_HPP_
#define MODELRENDERER_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"
#include "Components/Window.hpp"
#include "Exception.hpp"

namespace is::components {

    class ModelRendererComponent : public is::ecs::Component {
        public:
            ModelRendererComponent(std::shared_ptr<is::ecs::Entity> &e,
                                   std::string name,
                                   std::string wn,
                                   std::string matName = "",
                                   bool shadow = false);
            ~ModelRendererComponent() override = default;

            ModelRendererComponent(const ModelRendererComponent &) = delete;
            ModelRendererComponent &operator=(const ModelRendererComponent &) = delete;

            void deleteComponent() override;

            void initModelRenderer(const std::shared_ptr<is::components::WindowComponent>& ptr_window);
            [[nodiscard]] irr::scene::IAnimatedMeshSceneNode *getElement() const;
            std::string fileName;
            std::string materialName;
            std::string windowName;
            bool modelShadow;
            irr::scene::IAnimatedMeshSceneNode *node = nullptr;
    };

}

#endif /* !MODELRENDERER_HPP_ */

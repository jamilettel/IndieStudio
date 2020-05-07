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

namespace is::components {

    class ComponentModelRenderer : public is::ecs::Component {
        public:
            ComponentModelRenderer(std::shared_ptr<is::ecs::Entity> &e,
                                   const std::string &name,
                                   const std::string &wn);
            ~ComponentModelRenderer() = default;

            ComponentModelRenderer(const ComponentModelRenderer &) = delete;
            ComponentModelRenderer &operator=(const ComponentModelRenderer &) = delete;

            std::string fileName;
            std::string windowName;
            irr::scene::IAnimatedMeshSceneNode *node;
    };

}

#endif /* !ModelRenderer_HPP_ */

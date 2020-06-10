/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Animator
*/

#ifndef ANIMATOR_HPP_
#define ANIMATOR_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"
#include "ECS/Entity.hpp"
#include "Exception.hpp"
#include "Components/ModelRenderer.hpp"

namespace is::components {

    class AnimatorComponent : public is::ecs::Component {
        public:
            struct AnimatorElem {
                int start;
                int end;
                std::string name;
            };

            explicit AnimatorComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~AnimatorComponent() override = default;

            AnimatorComponent(const AnimatorComponent &) = delete;
            AnimatorComponent &operator=(const AnimatorComponent &) = delete;

            void deleteComponent() override;

            void changeAnimation(const std::string &anim, bool loop = true);

            std::vector<AnimatorElem> animators;
            std::string currentAnim;
    };

}

#endif /* !ANIMATOR_HPP_ */

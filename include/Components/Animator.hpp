/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Animator
*/

#ifndef Animator_HPP_
#define Animator_HPP_

#include <irrlicht.h>
#include <string>
#include <vector>
#include <memory>

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

            void changeAnimation(const std::string &anim);

            std::vector<AnimatorElem> animators;
            std::string currentAnim;
    };

}

#endif /* !Animator_HPP_ */

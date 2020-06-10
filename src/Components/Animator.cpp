/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Animator
*/

#include "Components/Animator.hpp"

using namespace is::components;
using namespace is::ecs;

AnimatorComponent::AnimatorComponent(std::shared_ptr<is::ecs::Entity> &e) :
Component(e)
{
}

void AnimatorComponent::deleteComponent()
{
}

void AnimatorComponent::changeAnimation(const std::string &anim, bool loop)
{
    if (anim == currentAnim)
        return;
    for (auto &elem : animators) {
        if (elem.name == anim) {
            auto renderer = getEntity()->getComponent<ModelRendererComponent>();

            if (renderer->get()->node) {
                renderer->get()->node->setFrameLoop(elem.start, elem.end);
                renderer->get()->node->setLoopMode(loop);
            }
            currentAnim = anim;
            return;
        }
    }
    throw is::exceptions::Exception("AnimatorComponent", "Animation not found");
}

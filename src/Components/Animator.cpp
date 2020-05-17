/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Animator
*/

#include "Components/Animator.hpp"

is::components::AnimatorComponent::AnimatorComponent(std::shared_ptr<is::ecs::Entity> &e) :
Component(e)
{

}

void is::components::AnimatorComponent::deleteComponent()
{
    
}

void is::components::AnimatorComponent::changeAnimation(const std::string &anim)
{
    bool animFound = false;

    if (anim == currentAnim)
        return;
    for (auto &elem : animators) {
        if (elem.name == anim) {
            getEntity()->getComponent<is::components::ModelRendererComponent>()->get()->node->setFrameLoop(elem.start, elem.end);
            animFound = true;
            currentAnim = anim;
        }
    }
    if (!animFound)
        throw is::exceptions::Exception("AnimatorComponent", "Animation not found");
}

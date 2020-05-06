/*
** EPITECH PROJECT, 2020
** Indie
** File description:
** collider component
*/

#include "Components/ColliderComponent.hpp"

using namespace is::components;

ColliderComponent::ColliderComponent(std::shared_ptr<is::ecs::Entity> &e, bool check):
    Component(e), activeCheck(check)
{}

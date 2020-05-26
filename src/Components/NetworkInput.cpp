/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** NetworkInputComponent
*/

#include "Components/NetworkInput.hpp"

using namespace is::components;
using namespace is::ecs;

NetworkInputComponent::NetworkInputComponent(
    std::shared_ptr<is::ecs::Entity> &e
    ):
    Component(e)
{}

void NetworkInputComponent::deleteComponent()
{}

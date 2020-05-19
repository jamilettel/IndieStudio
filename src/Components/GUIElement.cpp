/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** GUIElement
*/

#include "Components/GUIElement.hpp"

using namespace is::ecs;
using namespace is::components;

GUIElementComponent::GUIElementComponent(std::shared_ptr<Entity> &e):
    Component(e)
{}

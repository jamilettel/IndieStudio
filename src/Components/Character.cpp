/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Character
*/

#include "Components/Character.hpp"

using namespace is::components;
using namespace is::ecs;

CharacterComponent::CharacterComponent(
    std::shared_ptr<Entity> &e,
    int characterNumber
    ):
    Component(e), number(characterNumber)
{}

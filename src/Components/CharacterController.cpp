/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterController
*/

#include "Components/CharacterController.hpp"

is::components::ComponentCharacterController::ComponentCharacterController(std::shared_ptr<is::ecs::Entity> &e,
                                                                           const std::string &wn,
                                                                           float ps) :
Component(e)
{
    playerSpeed = ps;
    windowName = wn;
}

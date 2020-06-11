/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Fire
*/

#include "Components/Fire.hpp"

using namespace is::components;
using namespace is::ecs;

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

FireComponent::FireComponent(std::shared_ptr<Entity> &e, float lt):
    Component(e),
    lifeTime(lt),
    _explosionSound(
        e->addComponent<AudioComponent>(
            e,
            RESSOURCE("explosion.ogg"),
            SOUND
            ))
{
    _explosionSound.init();
    _explosionSound.toPlay();
}

void FireComponent::deleteComponent()
{
    
}

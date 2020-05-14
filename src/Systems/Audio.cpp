/*
** EPITECH PROJECT, 2020
** Systems/AudioSystem.cpp
** File description:
** 
*/

#include "Systems/Audio.hpp"
#include "Components/Audio.hpp"

#include <algorithm>

using namespace is::systems;
using namespace is::components;

void AudioSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<AudioComponent>(elem);
        ptr->init();
    }
}

void AudioSystem::start()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<AudioComponent>(elem);
        if (ptr->getStatus() == TO_PLAY) {
            ptr->play();
            ptr->nothing();
        }
    }

}

void AudioSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<AudioComponent>(elem);
        if (ptr->getStatus() == TO_PLAY && !ptr->isPlaying()) {
            ptr->play();
            ptr->nothing();
        } else if (ptr->getStatus() == TO_STOP && ptr->isPlaying()) {
            ptr->stop();
            ptr->nothing();
        }
    }
}

void AudioSystem::stop()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        if (!(elem->getEntity()->shouldBeDeleted()))
            continue;
        auto ptr = std::dynamic_pointer_cast<AudioComponent>(elem);
        ptr->stop();
    }
}

void AudioSystem::onTearDown()
{
}


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
    for (const auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<AudioComponent*>(elem.get());
        ptr->init();
    }
}

void AudioSystem::start()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<AudioComponent*>(elem.get());
        if (ptr->getStatus() == TO_PLAY) {
            ptr->play();
            ptr->nothing();
        }
    }

}

void AudioSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        const auto &ptr = static_cast<AudioComponent*>(elem.get());
        ptr->setVolume();
        if (ptr->getStatus() == TO_PLAY // && !ptr->isPlaying()
            ) {
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
    for (const auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        if (!(elem->getEntity()->shouldBeDeleted()))
            continue;
        const auto &ptr = static_cast<AudioComponent*>(elem.get());
        ptr->stop();
    }
}

void AudioSystem::onTearDown()
{
}


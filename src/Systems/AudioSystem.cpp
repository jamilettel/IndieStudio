/*
** EPITECH PROJECT, 2020
** Systems/AudioSystem.cpp
** File description:
** 
*/

#include "Systems/AudioSystem.hpp"
#include "Components/AudioComponent.hpp"

#include <algorithm>

using namespace is::system;
using namespace is::components;

void AudioSystem::awake()
{
}

void AudioSystem::start()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
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
        if (ptr->getStatus() == TO_PLAY) {
            ptr->play();
            ptr->nothing();
        } else if (ptr->getStatus() == TO_STOP) {
            ptr->stop();
            ptr->nothing();
        }
    }
}

void AudioSystem::stop()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<AudioComponent>(elem);
        ptr->stop();
    }
}

void AudioSystem::onTearDown()
{
}


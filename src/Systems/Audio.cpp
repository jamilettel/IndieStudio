/*
** EPITECH PROJECT, 2020
** Systems/SystemAudio.cpp
** File description:
** 
*/

#include "Systems/Audio.hpp"
#include "Components/Audio.hpp"

#include <algorithm>

using namespace is::systems;
using namespace is::components;

void SystemAudio::awake()
{
}

void SystemAudio::start()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentAudio).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentAudio>(elem);
        if (ptr->getStatus() == TO_PLAY) {
            ptr->play();
            ptr->nothing();
        }
    }

}

void SystemAudio::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentAudio).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentAudio>(elem);
        if (ptr->getStatus() == TO_PLAY) {
            ptr->play();
            ptr->nothing();
        } else if (ptr->getStatus() == TO_STOP) {
            ptr->stop();
            ptr->nothing();
        }
    }
}

void SystemAudio::stop()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentAudio).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentAudio>(elem);
        ptr->stop();
    }
}

void SystemAudio::onTearDown()
{
}


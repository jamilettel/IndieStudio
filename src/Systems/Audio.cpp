/*
** EPITECH PROJECT, 2020
** Systems/AudioSystem.cpp
** File description:
** 
*/

#include "Systems/Audio.hpp"
#include "Components/Audio.hpp"

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
    const auto &musics = _componentManager->getComponentsByType(typeid(AudioComponent).hash_code());
    if (musics.empty())
        return;

    const auto &mainMusic = static_cast<AudioComponent*>(musics[0].get());

    if (!mainMusic->isPlaying() && is::Game::getCurrentScene() != SCENE_GAME)
        mainMusic->play();
    else if (is::Game::getCurrentScene() == SCENE_GAME)
        mainMusic->pause();

    for (const auto &elem : musics) {
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
        } else if (ptr->getID() == GAME && is::Game::getCurrentScene() == SCENE_GAME && !ptr->isPlaying()) {
            ptr->play();
        }
    }
}

void AudioSystem::stop()
{
    bool first = true;

    for (const auto &elem : _componentManager->getComponentsByType(typeid(AudioComponent).hash_code())) {
        const auto &ptr = static_cast<AudioComponent*>(elem.get());
        if (first) {
            if (is::Game::getCurrentScene() == SCENE_GAME)
                ptr->pause();
            first = false;
            continue;
        }
        ptr->stop();
    }
}

void AudioSystem::onTearDown()
{
}


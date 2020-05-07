/*
** EPITECH PROJECT, 2020
** Indie
** File description:
** collider component
*/

#include "Components/AudioComponent.hpp"
#include "audio/AudioSoundSource.hpp"
#include "audio/AudioMusicSource.hpp"

using namespace is::components;
using namespace is::audio;

AudioComponent::AudioComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type) : Component(e), _status(NOTHING)
{
    if (type == SOUND)
        _audioSource = std::make_shared<AudioSoundSource>(filename);
    else
        _audioSource = std::make_shared<AudioMusicSource>(filename);
}

AudioComponent::AudioComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type, bool playOnStart) : Component(e)
{
    if (type == SOUND)
        _audioSource = std::make_shared<AudioSoundSource>(filename);
    else
        _audioSource = std::make_shared<AudioMusicSource>(filename);
    if (playOnStart)
        _status = TO_PLAY;
    else
        _status = NOTHING;
}

void AudioComponent::play()
{
    _audioSource->play();
}


void AudioComponent::pause()
{
    _audioSource->pause();
}

void AudioComponent::stop()
{
    _audioSource->stop();
}

void AudioComponent::toPlay()
{
    _status = TO_PLAY;
}

void AudioComponent::toStop()
{
    _status = TO_STOP;
}

void AudioComponent::nothing()
{
    _status = NOTHING;
}


SOUND_STATUS AudioComponent::getStatus() const
{
    return (_status);
}

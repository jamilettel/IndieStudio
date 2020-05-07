/*
** EPITECH PROJECT, 2020
** Indie
** File description:
** collider component
*/

#include "Components/Audio.hpp"
#include "Audio/AudioSoundSource.hpp"
#include "Audio/AudioMusicSource.hpp"

using namespace is::components;
using namespace is::audio;

AudioComponent::AudioComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type) : Component(e), _filename(filename), _status(NOTHING), _type(type)
{
}

AudioComponent::AudioComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type, bool playOnStart) : Component(e),_filename(filename),  _type(type)
{
    if (playOnStart)
        _status = TO_PLAY;
    else
        _status = NOTHING;
}

void AudioComponent::init()
{
    if (_type == SOUND)
        _audioSource = std::make_shared<AudioSoundSource>(_filename);
    else
        _audioSource = std::make_shared<AudioMusicSource>(_filename);
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

bool AudioComponent::isPlaying()
{
    return (_audioSource->isPlaying());
}

SOUND_STATUS AudioComponent::getStatus() const
{
    return (_status);
}

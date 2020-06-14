/*
** EPITECH PROJECT, 2020
** Indie
** File description:
** collider component
*/

#include "Components/Audio.hpp"

#include <utility>
#include "Audio/AudioSoundSource.hpp"
#include "Audio/AudioMusicSource.hpp"

using namespace is::components;
using namespace is::audio;

float AudioComponent::_volumeMusic = 50;
float AudioComponent::_volumeSound = 50;

AudioComponent::AudioComponent(std::shared_ptr<is::ecs::Entity> &e, std::string filename, SOUND_TYPE type) : Component(e), _filename(std::move(filename)), _status(NOTHING), _type(type), _id(OTHERS)
{
}

AudioComponent::AudioComponent(std::shared_ptr<is::ecs::Entity> &e, std::string filename, SOUND_TYPE type, bool playOnStart) : Component(e),_filename(std::move(filename)),  _type(type), _id(OTHERS)
{
    if (playOnStart)
        _status = TO_PLAY;
    else
        _status = NOTHING;
}

void AudioComponent::deleteComponent()
{
    
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

void AudioComponent::setVolume()
{
    if (_type == SOUND)
        _audioSource->setVolume(_volumeSound);
    else
        _audioSource->setVolume(_volumeMusic);
}

void AudioComponent::setLoop(bool loop)
{
    _audioSource->setLoop(loop);
}

void AudioComponent::setID(SOUND_ID id)
{
    _id = id;
}

SOUND_ID AudioComponent::getID() const
{
    return _id;
}

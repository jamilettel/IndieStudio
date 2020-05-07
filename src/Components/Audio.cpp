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

ComponentAudio::ComponentAudio(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type) : Component(e), _filename(filename), _status(NOTHING), _type(type)
{
}

ComponentAudio::ComponentAudio(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type, bool playOnStart) : Component(e),_filename(filename),  _type(type)
{
    if (playOnStart)
        _status = TO_PLAY;
    else
        _status = NOTHING;
}

void ComponentAudio::init()
{
    if (_type == SOUND)
        _audioSource = std::make_shared<AudioSoundSource>(_filename);
    else
        _audioSource = std::make_shared<AudioMusicSource>(_filename);
}

void ComponentAudio::play()
{
    _audioSource->play();
}


void ComponentAudio::pause()
{
    _audioSource->pause();
}

void ComponentAudio::stop()
{
    _audioSource->stop();
}

void ComponentAudio::toPlay()
{
    _status = TO_PLAY;
}

void ComponentAudio::toStop()
{
    _status = TO_STOP;
}

void ComponentAudio::nothing()
{
    _status = NOTHING;
}

bool ComponentAudio::isPlaying()
{
    return (_audioSource->isPlaying());
}

SOUND_STATUS ComponentAudio::getStatus() const
{
    return (_status);
}

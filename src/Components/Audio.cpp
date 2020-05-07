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

ComponentAudio::ComponentAudio(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type) : Component(e), _status(NOTHING)
{
    if (type == SOUND)
        _audioSource = std::make_shared<AudioSoundSource>(filename);
    else
        _audioSource = std::make_shared<AudioMusicSource>(filename);
}

ComponentAudio::ComponentAudio(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type, bool playOnStart) : Component(e)
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


SOUND_STATUS ComponentAudio::getStatus() const
{
    return (_status);
}

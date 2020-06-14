/*
** EPITECH PROJECT, 2020
** AudioSoundSource.hpp
** File description:
** AudioSoundSource
*/

#include "Audio/AudioSoundSource.hpp"
#include "Exception.hpp"

using namespace is::audio;
using namespace is::exceptions;

AudioSoundSource::AudioSoundSource(const std::string &filename) : _buffer(std::make_unique<sf::SoundBuffer>()), _sound(std::make_unique<sf::Sound>())
{
    if (!_buffer->loadFromFile(filename))
        throw (Exception("AudioSoundSource", "cant open music file"));
    _sound->setBuffer(*_buffer);
}

void AudioSoundSource::play()
{
    _sound->play();
}

void AudioSoundSource::pause()
{
    _sound->pause();
}

void AudioSoundSource::stop()
{
    _sound->stop();
}

bool AudioSoundSource::isPlaying()
{
    return _sound->getStatus() == sf::SoundSource::Status::Playing;
}

void AudioSoundSource::setVolume(float volume)
{
    _sound->setVolume(volume);
}

void AudioSoundSource::setLoop(bool loop)
{
    _sound->setLoop(loop);
}

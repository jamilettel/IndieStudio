/*
** EPITECH PROJECT, 2020
** AudioMusicSource.hpp
** File description:
** AudioMusicSource
*/

#include "Audio/AudioMusicSource.hpp"
#include "Exception.hpp"

using namespace is::audio;
using namespace is::exceptions;

AudioMusicSource::AudioMusicSource(const std::string &filename) : _music(std::make_unique<sf::Music>())
{
    if (!_music->openFromFile(filename))
        throw (Exception("AudioMusicSource", "cant open music file"));
}

void AudioMusicSource::play()
{
    _music->play();
}

void AudioMusicSource::pause()
{
    _music->pause();
}

void AudioMusicSource::stop()
{
    _music->stop();
}

bool AudioMusicSource::isPlaying()
{
    return _music->getStatus() == sf::SoundSource::Status::Playing;
}

void AudioMusicSource::setVolume(float volume)
{
    _music->setVolume(volume);
}

void AudioMusicSource::setLoop(bool loop)
{
    _music->setLoop(loop);
}

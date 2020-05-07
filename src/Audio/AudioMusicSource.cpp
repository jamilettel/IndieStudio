/*
** EPITECH PROJECT, 2020
** AudioMusicSource.hpp
** File description:
** .hpp
*/

#include "Audio/AudioMusicSource.hpp"
#include "Exception.hpp"

using namespace is::audio;
using namespace is::exceptions;

AudioMusicSource::AudioMusicSource(const std::string &filename) : _music()
{
    if (!_music.openFromFile(filename))
        throw (Exception("AudioMusicSource", "cant open music file"));
}

void AudioMusicSource::play()
{
    _music.play();
}

void AudioMusicSource::pause()
{
    _music.pause();
}

void AudioMusicSource::stop()
{
    _music.stop();
}

bool AudioMusicSource::isPlaying()
{
    if (_music.getStatus() == sf::SoundSource::Status::Playing)
        return (true);
    return (false);
}

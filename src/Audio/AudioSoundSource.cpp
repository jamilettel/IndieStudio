/*
** EPITECH PROJECT, 2020
** AudioSoundSource.hpp
** File description:
** .hpp
*/

#include "Audio/AudioSoundSource.hpp"
#include "Exception.hpp"
using namespace is::audio;
using namespace is::exceptions;

AudioSoundSource::AudioSoundSource(const std::string &filename) : _sound(), _buffer()
{
    if (!_buffer.loadFromFile(filename))
        throw (Exception("AudioSoundSource", "cant open music file"));
    _sound.setBuffer(_buffer);
}

void AudioSoundSource::play()
{
    _sound.play();
}

void AudioSoundSource::pause()
{
    _sound.pause();
}

void AudioSoundSource::stop()
{
    _sound.stop();
}

bool AudioSoundSource::isPlaying()
{
    if (_sound.getStatus() == sf::SoundSource::Status::Playing)
        return (true);
    return (false);
}

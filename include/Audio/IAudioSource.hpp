/*
** EPITECH PROJECT, 2020
** IAudioSource.hpp
** File description:
** IAudioSource
*/

#ifndef IAUDIOSOURCE_HPP_
#define IAUDIOSOURCE_HPP_

#include <SFML/Audio.hpp>

namespace is::audio {

    class IAudioSource {
        public:
            virtual ~IAudioSource() = default;
            virtual void play() = 0;
            virtual void pause() = 0;
            virtual void stop() = 0;
            virtual bool isPlaying() = 0;
            virtual void setVolume(float volume) = 0;
    };
}

#endif

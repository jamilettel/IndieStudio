/*
** EPITECH PROJECT, 2020
** IAudioSource.hpp
** File description:
** .hpp
*/

#ifndef IAUDIOSOURCE_HPP
#   define IAUDIOSOURCE_HPP

#   include <SFML/Audio.hpp>

namespace is::audio {

    class IAudioSource {
        public:
            virtual ~IAudioSource() = default;
            virtual void play() = 0;
            virtual void pause() = 0;
            virtual void stop() = 0;
    };
}

#endif

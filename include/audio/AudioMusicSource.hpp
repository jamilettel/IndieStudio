/*
** EPITECH PROJECT, 2020
** AudioMusicSource.hpp
** File description:
** .hpp
*/

#ifndef AUDIOMUSICSOURCE_HPP
#  define AUDIOMUSICSOURCE_HPP

#   include <SFML/Audio.hpp>
#   include "IAudioSource.hpp"

namespace is::audio {
    
    class AudioMusicSource : public IAudioSource {
        public:
            AudioMusicSource(const std::string &filename);
            void play();
            void pause();
            void stop();
        private:
            sf::Music _music;
    };
}

#endif

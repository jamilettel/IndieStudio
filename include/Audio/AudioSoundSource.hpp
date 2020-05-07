/*
** EPITECH PROJECT, 2020
** AudioSoundSource.hpp
** File description:
** .hpp
*/

#ifndef AUDIOSOUNDSOURCE_HPP
#  define AUDIOSOUNDSOURCE_HPP

#   include <SFML/Audio.hpp>
#   include "IAudioSource.hpp"

namespace is::audio {
    
    class AudioSoundSource : public IAudioSource {
        public:
            AudioSoundSource(const std::string &filename);
            void play();
            void pause();
            void stop();
            bool isPlaying();
        private:
            sf::Sound _sound;
            sf::SoundBuffer _buffer;
    };
}

#endif

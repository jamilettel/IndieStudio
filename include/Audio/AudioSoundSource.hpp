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
            explicit AudioSoundSource(const std::string &filename);
            void play() override;
            void pause() override;
            void stop() override;
            bool isPlaying() override;
        private:
            sf::Sound _sound;
            sf::SoundBuffer _buffer;
    };
}

#endif

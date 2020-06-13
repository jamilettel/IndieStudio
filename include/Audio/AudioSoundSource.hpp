/*
** EPITECH PROJECT, 2020
** AudioSoundSource.hpp
** File description:
** AudioSoundSource
*/

#ifndef AUDIOSOUNDSOURCE_HPP_
#define AUDIOSOUNDSOURCE_HPP_

#include <SFML/Audio.hpp>
#include "IAudioSource.hpp"

namespace is::audio {
    
    class AudioSoundSource : public IAudioSource {
        public:
            explicit AudioSoundSource(const std::string &filename);
            void play() override;
            void pause() override;
            void stop() override;
            bool isPlaying() override;
            void setVolume(float volume) override;
            void setLoop(bool loop) override;
        private:
            sf::Sound _sound;
            sf::SoundBuffer _buffer;
    };
}

#endif

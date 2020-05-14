/*
** EPITECH PROJECT, 2020
** AudioMusicSource.hpp
** File description:
** .hpp
*/

#ifndef AUDIOMUSICSOURCE_HPP
#  define AUDIOMUSICSOURCE_HPP

#include <SFML/Audio.hpp>
#include "IAudioSource.hpp"

namespace is::audio {
    
    class AudioMusicSource : public IAudioSource {
        public:
            explicit AudioMusicSource(const std::string &filename);
            void play() override;
            void pause() override;
            void stop() override;
            bool isPlaying() override;
            void setVolume(float volume) override;
    private:
            sf::Music _music;
    };
}

#endif

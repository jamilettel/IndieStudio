/*
** EPITECH PROJECT, 2020
** AudioMusicSource.hpp
** File description:
** AudioSource
*/

#ifndef AUDIOMUSICSOURCE_HPP_
#define AUDIOMUSICSOURCE_HPP_

#include <memory>
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
            void setLoop(bool loop) override;
    private:
            std::unique_ptr<sf::Music> _music;
    };
}

#endif

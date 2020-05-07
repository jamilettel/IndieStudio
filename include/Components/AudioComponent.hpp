/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef AUDIOCOMPONENT_HPP_
#define AUDIOCOMPONENT_HPP_

#include <vector>
#include "ECS/Component.hpp"
#include "audio/IAudioSource.hpp"
#include <memory>

namespace is::components {

    enum SOUND_TYPE {SOUND, MUSIC};
    enum SOUND_STATUS {NOTHING, TO_PLAY, TO_STOP};

    class AudioComponent: public is::ecs::Component {

    public:
        AudioComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type);
        AudioComponent(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type, bool playOnStart);
        ~AudioComponent() = default;

        AudioComponent(const AudioComponent &) = delete;
        AudioComponent &operator=(const AudioComponent &) = delete;

        void play();
        void pause();
        void stop();
        void toPlay();
        void toStop();
        void nothing();

        SOUND_STATUS getStatus() const;

    private:
        std::shared_ptr<is::audio::IAudioSource> _audioSource;
        SOUND_STATUS _status;
    };

}

#endif /* !AUDIOCOMPONENT_HPP_ */

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
#include "Audio/IAudioSource.hpp"
#include <memory>

namespace is::components {

    enum SOUND_TYPE {SOUND, MUSIC};
    enum SOUND_STATUS {NOTHING, TO_PLAY, TO_STOP};

    class ComponentAudio: public is::ecs::Component {

    public:
        ComponentAudio(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type);
        ComponentAudio(std::shared_ptr<is::ecs::Entity> &e, const std::string &filename, SOUND_TYPE type, bool playOnStart);
        ~ComponentAudio() = default;

        ComponentAudio(const ComponentAudio &) = delete;
        ComponentAudio &operator=(const ComponentAudio &) = delete;

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

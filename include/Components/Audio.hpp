/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef AUDIOCOMPONENT_HPP_
#define AUDIOCOMPONENT_HPP_

#include "Audio/IAudioSource.hpp"
#include "ECS/Component.hpp"

namespace is::components {

    enum SOUND_TYPE {SOUND, MUSIC};
    enum SOUND_STATUS {NOTHING, TO_PLAY, TO_STOP};
    enum SOUND_ID {GAME, MENU, OTHERS};

    class AudioComponent: public is::ecs::Component {
        public:
            AudioComponent(std::shared_ptr<is::ecs::Entity> &e, std::string filename, SOUND_TYPE type);
            AudioComponent(std::shared_ptr<is::ecs::Entity> &e, std::string filename, SOUND_TYPE type, bool playOnStart);
            ~AudioComponent() override = default;

            AudioComponent(const AudioComponent &) = delete;
            AudioComponent &operator=(const AudioComponent &) = delete;

            void init();
            void play();
            void pause();
            void stop();
            void toPlay();
            void toStop();
            void nothing();
            bool isPlaying();

            [[nodiscard]] SOUND_STATUS getStatus() const;
            void setID(SOUND_ID id);
            SOUND_ID getID() const;

            void deleteComponent() override;

            void setLoop(bool loop);
            void setVolume();
            static float _volumeMusic;
            static float _volumeSound;

        private:
            std::string _filename;
            std::shared_ptr<is::audio::IAudioSource> _audioSource;
            SOUND_STATUS _status;
            SOUND_TYPE _type;
            SOUND_ID _id;
    };

}

#endif /* !AUDIOCOMPONENT_HPP_ */

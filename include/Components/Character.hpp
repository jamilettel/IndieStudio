/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Character
*/

#ifndef CHARACTERCOMPONENT_HPP_
#define CHARACTERCOMPONENT_HPP_

#include "ECS/Component.hpp"

namespace is::components
{
    class CharacterComponent : public is::ecs::Component {
        public:
            CharacterComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~CharacterComponent();

            void setTimePlaying(size_t time) noexcept;
            void setNbBombPosed(size_t nbBombPosed) noexcept;
            void setNbBonusCollected(size_t nbBonusCollected) noexcept;
            void setNbCharactersKilled(size_t nbCharactersKilled) noexcept;

            int getTimePlaying() const noexcept;
            int getNbBombPosed() const noexcept;
            int getNbBonueCollected() const noexcept;
            int getNbCharactersKilled() const noexcept;

        private:
            size_t _timePlaying = 0;
            size_t _nbBombPosed = 0;
            size_t _nbBonusCollected = 0;
            size_t _nbCharactersKilled = 0;
    };
}


#endif /* !CHARACTER_HPP_ */

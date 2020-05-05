/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>

#include "Scene.hpp"

namespace is {

    class Game {
        public:
            Game();
            ~Game();

        protected:
        private:
            std::vector<is::Scene> _scenes;
    };

}

#endif /* !GAME_HPP_ */

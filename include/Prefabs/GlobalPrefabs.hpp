/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#ifndef GLOBALPREFABS_HPP_
#define GLOBALPREFABS_HPP_

#include <memory>

#include "ECS/Entity.hpp"

#include "Components/Window.hpp"

namespace prefabs {

    class GlobalPrefabs {
        public:
            static std::shared_ptr<is::ecs::Entity> createGlobalPrefab();
    };

}

#endif /* !GLOBALPREFABS_HPP_ */

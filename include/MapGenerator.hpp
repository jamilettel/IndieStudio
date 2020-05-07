/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "ECS/AScene.hpp"

class MapGenerator
{
public:
    MapGenerator() = default;
    MapGenerator(const MapGenerator& other) = default;
    MapGenerator& operator=(const MapGenerator& rhs) = default;
    ~MapGenerator() = default;

    void generateMap(is::ecs::AScene &sc);
};

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "ECS/AScene.hpp"

#ifndef MAP_GENERATOR
#define MAP_GENERATOR

class MapGenerator {
    public:
        MapGenerator() = default;
        MapGenerator(const MapGenerator& other) = default;
        MapGenerator& operator=(const MapGenerator& rhs) = default;
        ~MapGenerator() = default;

        void generateMap(is::ecs::AScene &sc, int seed, int widht, int height, std::vector<std::shared_ptr<is::ecs::Component>> network);
    
    private:
        static std::vector<size_t> permTable;
        bool checkSpawnBlock(int x, int y, int width, int height);
        void generatePermTable(int seed);
        std::vector<std::vector<int>> generateArray(int width, int height);
        float getVectorPermTable(float x, float y, float x0, float y0, int addX, int);
        float generatePerlinNoise(float x, float y, float res);
};

#endif

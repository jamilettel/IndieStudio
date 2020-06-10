/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "ECS/AScene.hpp"

#ifndef MAP_GENERATOR_HPP_
#define MAP_GENERATOR_HPP_

class MapGenerator {
    public:
        MapGenerator() = default;
        MapGenerator(const MapGenerator& other) = default;
        MapGenerator& operator=(const MapGenerator& rhs) = default;
        ~MapGenerator() = default;

        void generateMap(is::ecs::AScene &sc, int seed, int width, int height, std::vector<std::shared_ptr<is::ecs::Component>> network);
        void createMap(is::ecs::AScene &sc, std::vector<std::vector<int>> arrayMap, int mid_w, int mid_h, std::vector<std::shared_ptr<is::ecs::Component>> network);
    
    private:
        float getVectorPermTable(float x, float y, float x0, float y0, int addX, int);
        std::vector<std::vector<int>> generateArray(int width, int height);
        bool checkSpawnBlock(int x, int y, int width, int height);
        float generatePerlinNoise(float x, float y, float res);
        void generatePermTable(int seed);


    private:
        static std::vector<size_t> permTable;
};

#endif

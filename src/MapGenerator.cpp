/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#include "MapGenerator.hpp"
#include <random>

using namespace is;

std::vector<size_t> MapGenerator::permTable;

const std::vector<std::vector<float>> gradientVector
{
    {static_cast<float>(1.0f / sqrt(2)), static_cast<float>(1.0f / sqrt(2))},
    {static_cast<float>(-(1.0f / sqrt(2))), static_cast<float>(1.0f / sqrt(2))},
    {static_cast<float>(1.0f / sqrt(2)), static_cast<float>(-(1.0f / sqrt(2)))},
    {static_cast<float>(-(1.0f / sqrt(2))), static_cast<float>(-(1.0f / sqrt(2)))},
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

void MapGenerator::generatePermTable(int seed)
{
    for (size_t i = 0; i < 300; permTable.push_back(i), i++);

    std::default_random_engine permRandom(seed);
    shuffle(permTable.begin(), permTable.end(), permRandom);
}

float MapGenerator::getVectorPermTable(float x, float y, float x0, float y0, int addX, int addY)
{
    int tmpX = (static_cast<int>(x0) & 255) + addX;
    int tmpY = (static_cast<int>(y0) & 255) + addY;

    std::cout << "[index] : " << tmpX << " - " << permTable[tmpY] << std::endl;
    int tmpVector = permTable[tmpX + permTable[tmpY]] % 8;
    return ((gradientVector[tmpVector][0] * (x - (x0 + addX))) + 
            (gradientVector[tmpVector][1] * (y - (y0 + addY))));
}

float MapGenerator::generatePerlinNoise(float x, float y, float res)
{
    x /= res;
    y /= res;
    float x0 = trunc(x);
    float y0 = trunc(y);
 
    float Cx = (3 * pow(x - x0, 2)) - (2 * pow(x - x0, 3));
    float Cy = (3 * pow(y - y0, 2)) - (2 * pow(y - y0, 3));
    
    float L1 = getVectorPermTable(x, y, x0, y0, 0, 0) +
        (Cx * (getVectorPermTable(x, y, x0, y0, 1, 0) -
               getVectorPermTable(x, y, x0, y0, 0, 0))); 
    float L2 = getVectorPermTable(x, y, x0, y0, 0, 1) +
        (Cx * (getVectorPermTable(x, y, x0, y0, 1, 1) -
               getVectorPermTable(x, y, x0, y0, 0, 1)));
    
    return (L1 + (Cy * (L2 - L1)));
}

bool MapGenerator::checkSpawnBlock(int x, int y, int width, int height)
{
    if ((x == 1 && y == 1) || (x == 2 && y == 1) ||
        (x == 1 && y == 2))
        return (true);
    if  ((x == width - 2 && y == 1) || (x == width - 3 && y == 1) || 
         (x == width - 2 && y == 2))
        return (true);
    if ((x == 1 && y == height - 2) || (x == 2 && y == height - 2) || 
        (x == 1 && y == height - 3))
        return (true);
    return (x == width - 2 && y == height - 2) ||
           (x == width - 3 && y == height - 2) ||
           (x == width - 2 && y == height - 3);
}

std::vector<std::vector<int>> MapGenerator::generateArray(int width, int height)
{
    std::vector<std::vector<int>> toReturn;
    for (int i = 0; i < height; i++) {
        toReturn.emplace_back(15);
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || j == width - 1 || i == height -1)
                toReturn[i][j] = 3;
            else if (!(i % 2) && !(j % 2))
                toReturn[i][j] = 2;
            else if (checkSpawnBlock(j, i, width, height))
                toReturn[i][j] = 0;
            else
                toReturn[i][j] = (int)round((generatePerlinNoise((float)j, (float)i, 1.1) + 1) * (float)0.5);
        }
    }
    return (toReturn);
}

void MapGenerator::generateMap(ecs::AScene &sc, int seed, int width, int height, std::vector<std::shared_ptr<is::ecs::Component>> network)
{
    int mid_w = width / 2;
    int mid_h = height / 2;

    generatePermTable(seed);
    std::vector<std::vector<int>> arrayMap = generateArray(width, height);

    for (int i = -mid_w; i < mid_w + 1; i++) {
        for (int j = -mid_h; j < mid_h + 1; j++) {
            sc.initEntity(prefabs::GlobalPrefabs::createGrassBlock(irr::core::vector3df(j * 3, -3, i * 3)));
            if (arrayMap[j + mid_h][i + mid_w] == 3) {
                sc.initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(j * 3, 0, i * 3)));
                sc.initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(j * 3, 3, i * 3)));
            } else if (arrayMap[j + mid_h][i + mid_w] == 2) {
                sc.initEntity(prefabs::GlobalPrefabs::createCenterBlock(irr::core::vector3df(j * 3, 0, i * 3)));
            } else if (arrayMap[j + mid_h][i + mid_w] == 1) {
                if (network.empty()) {
                    sc.initEntity(prefabs::GlobalPrefabs::createBreakableBlock(irr::core::vector3df(j * 3, 0, i * 3)));
                } else {
                    const auto &nw = static_cast<is::components::NetworkComponent*>(network[0].get());
                    if (nw->playerIdx == 0) {
                        sc.initEntity(prefabs::GlobalPrefabs::createBreakableBlock(irr::core::vector3df(j * 3, 0, i * 3)));
                        nw->writeQueue.push("evt bb " + std::to_string(nw->lobby) +
                                            " " + std::to_string(j * 3.0f) +
                                            " " + std::to_string(i * 3.0f) + " \n");
                    }
                }
            }
        }
    }
}

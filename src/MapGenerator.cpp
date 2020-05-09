/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MapGenerator
*/

#include "MapGenerator.hpp"

using namespace is;

void MapGenerator::generateMap(ecs::AScene &sc)
{
    int width = 15, height = 13;
    int mid_w = width / 2;
    int mid_h = height / 2;

    srand(time(NULL));

    // create ground
    for (int i = -mid_w; i < mid_w + 1; i++)
        for (int j = -mid_h; j < mid_h + 1; j++)
            sc.initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(j * 3, -3, i * 3)));
    
    // create walls
    for (int i = -mid_w; i < mid_w + 1; i++)
        sc.initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(-mid_h * 3, 0, i * 3)));
    for (int i = -mid_w; i < mid_w + 1; i++)
        sc.initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(mid_h * 3, 0, i * 3)));
    for (int i = -mid_h; i < mid_h + 1; i++)
        sc.initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(i * 3, 0, -mid_w * 3)));
    for (int i = -mid_h; i < mid_h + 1; i++)
        sc.initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(i * 3, 0, mid_w * 3)));
    
    // create middle walls
    for (int i = -mid_w + 1; i < mid_w; i++)
        for (int j = -mid_h + 1; j < mid_h; j++)
            if (i % 2 && !(j % 2))
                sc.initEntity(prefabs::GlobalPrefabs::createWallBlock(irr::core::vector3df(j * 3, 0, i * 3)));
    //for (int i = -mid_w + 1; i < mid_w; i++)
    //    for (int j = -mid_h + 1; j < mid_h; j++)
    //        if (!(i % 2 && !(j % 2)) && rand() % 4 == 0 && !(i == 0 && j == 0))
    //            sc.initEntity(prefabs::GlobalPrefabs::createBreakableBlock(irr::core::vector3df(j * 3, 0, i * 3)));
}

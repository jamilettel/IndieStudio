/*
** EPITECH PROJECT, 2020
** IDGenerator.cpp
** File description:
** 
*/

#include "IDGenerator.hpp"

size_t IDGenerator::id = 0;

size_t IDGenerator::getNewID()
{
    id++;
    return id;
}


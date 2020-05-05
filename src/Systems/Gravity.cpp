/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Gravity
*/

#include "Systems/Gravity.hpp"

Gravity::Gravity()
{
}

Gravity::~Gravity()
{
}

void Gravity::awake()
{
    std::cout << "awake" << std::endl;
}

void Gravity::start()
{
    std::cout << "start" << std::endl;
}

void Gravity::update()
{
    std::cout << "update" << std::endl;
}

void Gravity::stop()
{
    std::cout << "stop" << std::endl;
}

void Gravity::onTearDown()
{
    std::cout << "onTearDown" << std::endl;
}


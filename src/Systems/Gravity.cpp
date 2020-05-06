/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemGravity
*/

#include "Systems/Gravity.hpp"

SystemGravity::SystemGravity()
{
}

SystemGravity::~SystemGravity()
{
}

void SystemGravity::awake()
{
    std::cout << "awake" << std::endl;
}

void SystemGravity::start()
{
    std::cout << "start" << std::endl;
}

void SystemGravity::update()
{
    std::cout << "update" << std::endl;
}

void SystemGravity::stop()
{
    std::cout << "stop" << std::endl;
}

void SystemGravity::onTearDown()
{
    std::cout << "onTearDown" << std::endl;
}


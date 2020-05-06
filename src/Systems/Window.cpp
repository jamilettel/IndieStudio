/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemWindow
*/

#include "Systems/Window.hpp"

SystemWindow::SystemWindow()
{
}

SystemWindow::~SystemWindow()
{
}

void SystemWindow::awake()
{
    std::cout << "awake" << std::endl;
}

void SystemWindow::start()
{
    std::cout << "start" << std::endl;
}

void SystemWindow::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code())) {
        auto ptr = elem;
        std::cout << "lol" << std::endl;
    }
    
    std::cout << "update" << std::endl;
}

void SystemWindow::stop()
{
    std::cout << "stop" << std::endl;
}

void SystemWindow::onTearDown()
{
    std::cout << "onTearDown" << std::endl;
}


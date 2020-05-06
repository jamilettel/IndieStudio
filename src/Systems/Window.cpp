/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemWindow
*/

#include "Systems/Window.hpp"

using namespace irr;

SystemWindow::SystemWindow()
{
}

SystemWindow::~SystemWindow()
{
}

void SystemWindow::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentWindow>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemWindow", "Could not get ComponentWindow pointer");
        ptr->device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(1920, 1080), 32, false, false, false, &ptr->eventManager);
        if (!ptr->device)
            throw new is::exceptions::Exception("SystemWindow", "Could not create new irr device");
        ptr->driver = ptr->device->getVideoDriver();
        if (!ptr->driver)
            throw new is::exceptions::Exception("SystemWindow", "Could not create video driver");
        ptr->scenemgr = ptr->device->getSceneManager();
        if (!ptr->scenemgr)
            throw new is::exceptions::Exception("SystemWindow", "Could not create scene manager");
    }
}

void SystemWindow::start()
{

}

void SystemWindow::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentWindow>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemWindow", "Could not get ComponentWindow pointer");
        if (!ptr->device->run()) {
            is::Game::isRunning = false;
            return;
        }
        ptr->driver->beginScene(true, true, video::SColor(255,255,255,255));
        ptr->scenemgr->drawAll();
        ptr->driver->endScene();
    }
}

void SystemWindow::stop()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(ComponentWindow).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<ComponentWindow>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemWindow", "Could not get ComponentWindow pointer");
        ptr->device->drop();
    }
}

void SystemWindow::onTearDown()
{

}


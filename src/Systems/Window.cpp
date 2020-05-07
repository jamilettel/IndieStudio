/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SystemWindow
*/

#include "Systems/Window.hpp"

using namespace irr;

void is::systems::SystemWindow::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentWindow).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentWindow>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemWindow", "Could not get ComponentWindow pointer");

        ptr->device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(1600, 900), 32, false, true, true, &ptr->eventManager);
        if (!ptr->device)
            throw new is::exceptions::Exception("SystemWindow", "Could not create new irr device");

        std::wstring wide_string = std::wstring(ptr->windowName.begin(), ptr->windowName.end());
        const wchar_t* result = wide_string.c_str();
        ptr->device->setWindowCaption(result);
        ptr->driver = ptr->device->getVideoDriver();
        if (!ptr->driver)
            throw new is::exceptions::Exception("SystemWindow", "Could not create video driver");

        ptr->scenemgr = ptr->device->getSceneManager();
        if (!ptr->scenemgr)
            throw new is::exceptions::Exception("SystemWindow", "Could not create scene manager");
    }
}

void is::systems::SystemWindow::start()
{

}

void is::systems::SystemWindow::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentWindow).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentWindow>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemWindow", "Could not get ComponentWindow pointer");

        if (!ptr->device->run()) {
            is::Game::isRunning = false;
            return;
        }
        ptr->driver->beginScene(true, true, video::SColor(255, 255, 255, 255));
        ptr->scenemgr->drawAll();
        ptr->driver->endScene();
    }
}

void is::systems::SystemWindow::stop()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::ComponentWindow).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::ComponentWindow>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("SystemWindow", "Could not get ComponentWindow pointer");
        ptr->device->drop();
    }
}

void is::systems::SystemWindow::onTearDown()
{

}


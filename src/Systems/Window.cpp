/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WindowSystem
*/

#include "Systems/Window.hpp"

using namespace irr;

void is::systems::WindowSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::WindowComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("WindowSystem", "Could not get WindowComponent pointer");

        ptr->device = createDevice(video::EDT_OPENGL, ptr->windowSize, 32, ptr->fullscreen, true, true, &ptr->eventManager);
        if (!ptr->device)
            throw is::exceptions::Exception("WindowSystem", "Could not create new irr device");

        ptr->eventManager.setDeviceContext(*ptr->device);
        ptr->device->setEventReceiver(&ptr->eventManager);
        std::wstring wide_string = std::wstring(ptr->windowName.begin(), ptr->windowName.end());
        const wchar_t* result = wide_string.c_str();
        ptr->device->setWindowCaption(result);
        ptr->driver = ptr->device->getVideoDriver();
        if (!ptr->driver)
            throw is::exceptions::Exception("WindowSystem", "Could not create video driver");

        ptr->scenemgr = ptr->device->getSceneManager();
        if (!ptr->scenemgr)
            throw is::exceptions::Exception("WindowSystem", "Could not create scene manager");

        ptr->eventManager.addEventKeyReleased(irr::KEY_ESCAPE, [](){
            is::Game::isRunning = false;
        });
    }
}

void is::systems::WindowSystem::start()
{

}

void is::systems::WindowSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::WindowComponent>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("WindowSystem", "Could not get WindowComponent pointer");
        if (!ptr->device->run()) {
            std::cout << ptr->windowName << std::endl;
            is::Game::isRunning = false;
            return;
        }
        ptr->driver->beginScene(true, true, video::SColor(255, 255, 255, 255));
        ptr->scenemgr->drawAll();
        ptr->driver->endScene();
    }
}

void is::systems::WindowSystem::stop()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::WindowComponent>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("WindowSystem", "Could not get WindowComponent pointer");
        ptr->device->drop();
    }
}

void is::systems::WindowSystem::onTearDown()
{

}


/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WindowSystem
*/

#include "Systems/Window.hpp"

using namespace irr;
using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void WindowSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<WindowComponent>(elem);
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

        ptr->canvas = ptr->device->getGUIEnvironment();
        if (!ptr->canvas)
            throw is::exceptions::Exception("WindowSystem", "Could not create gui environment");
        
        ptr->eventManager.addEventKeyReleased(irr::KEY_ESCAPE, [](){
            is::Game::isRunning = false;
        });
        #ifndef __APPLE__
            ptr->joystickSupport = ptr->device->activateJoysticks(ptr->joysticks);
        #endif
    }
}

void WindowSystem::start()
{
    std::vector<std::shared_ptr<Component>> &time =
        _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());

    if (!time.size())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<TimeComponent *>(time[0].get()));
}

void WindowSystem::manageJoysticks(std::shared_ptr<WindowComponent> &ptr)
{
    ptr->joystickRefreshRemainingTime += _time->get().getCurrentIntervalSeconds();
    if (ptr->joystickRefreshRemainingTime < ptr->joystickRefresh)
        return;
    ptr->joystickRefreshRemainingTime = 0;
    ptr->device->activateJoysticks(ptr->joysticks);
    for (size_t i = 0; i < ptr->joysticks.size(); i++) {
        std::cerr << time(NULL) << std::endl;
        std::cerr << ptr->joysticks[i].Name.c_str() << std::endl;
        std::cerr << "ID: " << ptr->joysticks[i].Joystick << std::endl;
        std::cerr << "Axes: " << ptr->joysticks[i].Axes << std::endl;
        std::cerr << "Buttons: " << ptr->joysticks[i].Buttons << std::  endl;
    }
}

void WindowSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<WindowComponent>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("WindowSystem", "Could not get WindowComponent pointer");
        if (!ptr->device->run()) {
            std::cout << ptr->windowName << std::endl;
            is::Game::isRunning = false;
            return;
        }
        #ifndef __APPLE__
            if (ptr->joystickSupport)
                manageJoysticks(ptr);
        #endif
        ptr->driver->beginScene(true, true, video::SColor(255, 255, 255, 255));
        ptr->scenemgr->drawAll();
        ptr->canvas->drawAll();
        ptr->driver->endScene();
    }
}

void WindowSystem::stop()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<WindowComponent>(elem);
        if (!ptr)
            throw new is::exceptions::Exception("WindowSystem", "Could not get WindowComponent pointer");
        ptr->device->drop();
    }
}

void WindowSystem::onTearDown()
{

}


/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WindowSystem
*/

#include "Systems/Window.hpp"
#include "Components/Image.hpp"
#include "Components/Button.hpp"

using namespace irr;
using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void WindowSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
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
        ptr->device->getCursorControl()->setVisible(false);
    }
}

void WindowSystem::start()
{
    std::vector<std::shared_ptr<Component>> &time =
        _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());

    if (time.empty())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<TimeComponent *>(time[0].get()));
    sortGUIElements();
}

void WindowSystem::sortGUIElements()
{
    auto &images = _componentManager->getComponentsByType(typeid(ImageComponent).hash_code());
    auto &buttons = _componentManager->getComponentsByType(typeid(ButtonComponent).hash_code());


    std::sort(
        images.begin(), images.end(),
        [] (const std::shared_ptr<Component> &img1, const std::shared_ptr<Component> &img2)->bool {
            return static_cast<ImageComponent *>(img1.get())->layer < static_cast<ImageComponent *>(img2.get())->layer;
        });
    std::sort(
        buttons.begin(), buttons.end(),
        [] (const std::shared_ptr<Component> &btn1, const std::shared_ptr<Component> &btn2)->bool {
            return static_cast<ButtonComponent *>(btn1.get())->layer < static_cast<ButtonComponent *>(btn2.get())->layer;
        });
    for (size_t i = 0, b = 0; b < buttons.size() || i < images.size();) {
        ButtonComponent *btn = nullptr;
        ImageComponent *img = nullptr;

        if (buttons.size() > b)
            btn = static_cast<ButtonComponent *>(buttons[b].get());
        if (images.size() > i)
            img = static_cast<ImageComponent *>(images[i].get());
        if (img && (!btn || img->layer < btn->layer)) {
            img->bringToFront();
            i++;
        } else if (btn) {
            btn->bringToFront();
            b++;
        }
    }
}

void WindowSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<WindowComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("WindowSystem", "Could not get WindowComponent pointer");
        if (!ptr->device->run()) {
            std::cout << ptr->windowName << std::endl;
            is::Game::isRunning = false;
            return;
        }
        ptr->driver->beginScene(true, true, video::SColor(255, 255, 255, 255));
        ptr->scenemgr->drawAll();
        ptr->canvas->drawAll();
        ptr->driver->endScene();
        is::components::WindowComponent::_windowsDimensions[ptr->windowName] = std::pair<int, int>(ptr->driver->getScreenSize().Width, ptr->driver->getScreenSize().Height);
    }
}

void WindowSystem::stop()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(WindowComponent).hash_code())) {
        if (!(elem->getEntity()->shouldBeDeleted()))
            continue;
        auto ptr = std::dynamic_pointer_cast<WindowComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("WindowSystem", "Could not get WindowComponent pointer");
        ptr->device->drop();
    }
}

void WindowSystem::onTearDown()
{
}

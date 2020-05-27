/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** WindowSystem
*/

#include "Systems/Window.hpp"
#include "Components/Image.hpp"
#include "Components/Button.hpp"
#include "Components/Text.hpp"
#include "Components/Texture.hpp"
#include "Components/Transform.hpp"
#include "Prefabs/GlobalPrefabs.hpp"

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
        ptr->device->getCursorControl()->setVisible(false);
        ptr->device->activateJoysticks(ptr->joysticks);

        for (size_t i = 0; i < ptr->joysticks.size(); i++) {
            ptr->joysticks[i].Joystick = i;
            initRuntimeEntity(is::prefabs::GlobalPrefabs::createJoystickCursor(ptr->joysticks[i].Joystick, ptr), true);
        }

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
    auto guiElements = _componentManager->getComponentsByType(typeid(ImageComponent).hash_code());
    auto &buttons = _componentManager->getComponentsByType(typeid(ButtonComponent).hash_code());
    auto &texts = _componentManager->getComponentsByType(typeid(TextComponent).hash_code());

    guiElements.reserve(guiElements.size() + buttons.size() + texts.size());
    std::for_each(buttons.begin(), buttons.end(), [&guiElements] (auto &elem) {guiElements.push_back(elem);});
    std::for_each(texts.begin(), texts.end(), [&guiElements] (auto &elem) {guiElements.push_back(elem);});

    std::sort(
        guiElements.begin(), guiElements.end(),
        [] (const std::shared_ptr<Component> &img1, const std::shared_ptr<Component> &img2)->bool {
            return static_cast<GUIElementComponent *>(img1.get())->layer < static_cast<GUIElementComponent *>(img2.get())->layer;
        });
    std::for_each(
        guiElements.begin(), guiElements.end(),
        [] (auto &elem) {
            static_cast<GUIElementComponent *>(elem.get())->bringToFront();
        });
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
        for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::TextureComponent).hash_code())) {
            auto texture = std::dynamic_pointer_cast<is::components::TextureComponent>(elem);
            std::pair<int, int> wDim = is::components::WindowComponent::_windowsDimensions["Indie Studio"];

            ptr->driver->draw2DImage(
                texture->getNode(),
                irr::core::rect<s32>(
                    wDim.first * texture->getPosition().X / 100,
                    wDim.second * texture->getPosition().Y / 100,
                    wDim.first * texture->getPosition().X / 100 + wDim.first * texture->getSize().X / 100,
                    wDim.second * texture->getPosition().Y / 100 + wDim.second * texture->getSize().Y / 100
                ),
                irr::core::rect<s32>(0, 0, texture->getNode()->getOriginalSize().Width, texture->getNode()->getOriginalSize().Height),
                0, 0, true
            );
        }
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

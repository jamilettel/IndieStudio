/*
** EPITECH PROJECT, 2020
** Systems/ParticuleSystem.cpp
** File description:
** 
*/

#include "Systems/Preset.hpp"
#include "Components/Preset.hpp"

using namespace is::systems;
using namespace is::components;

void PresetSystem::awake()
{
    auto windows = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());

    if (windows.empty())
        throw is::exceptions::Exception(
            "Component missing",
            "Window component required for Keyboard Input System");
    auto window = std::dynamic_pointer_cast<WindowComponent>(windows[0]);
    _eventManager.emplace(window->eventManager);
    _joysticks = window->joysticks;
    _window = window;
}

void PresetSystem::start()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &components = _componentManager->getComponentsByType(typeid(PresetComponent).hash_code());

    _eventManager->get().resetLastKeyPressed();
    auto *p = static_cast<PresetComponent *>(components[0].get());
    p->_onSelect = true;

    for (auto &preset : components) {
        auto *p = static_cast<PresetComponent *>(preset.get());
        p->_toChange.reset();
        p->_toChangeUI.reset();
    }
}

void PresetSystem::update()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &components = _componentManager->getComponentsByType(typeid(PresetComponent).hash_code());

    for (auto &preset : components) {
        auto *p = static_cast<PresetComponent *>(preset.get());
        if (!p->_onSelect)
            continue;
        if (!p->_toChange.has_value()) {
            p->_toChange.reset();
            _eventManager->get().resetLastKeyPressed();
            continue;
        }
        for (int i = 0; PresetComponent::EquivalentKeys[i]._key != EKEY_CODE::KEY_KEY_CODES_COUNT && p->_callerID == -1; i++) {
            if (PresetComponent::EquivalentKeys[i]._key == _eventManager->get().getLastKeyPressed() && !p->getKeyboardPreset().isBound(PresetComponent::EquivalentKeys[i]._key)) {
                p->getKeyboardPreset().bind(PresetComponent::EquivalentKeys[i]._key, p->_toChange.value());
                std::get<0>(p->_toChangeUI.value()).get().setText(PresetComponent::getEquivalentKey(PresetComponent::EquivalentKeys[i]._key));
                p->_toChangeUI.reset();
                p->_toChange.reset();
                _eventManager->get().resetLastKeyPressed();
                break;
            }
        }
        for (int i = 0; PresetComponent::EquivalentButtons[i]._button != -9999; i++) {
            if (_eventManager->get().isJoystickButtonPressed(p->_callerID, (PresetComponent::EquivalentButtons[i]._button * -1) - 1) && !p->getJoystickPreset().isButtonBound(PresetComponent::EquivalentButtons[i]._button)) {
                p->getJoystickPreset().bindButton(PresetComponent::EquivalentButtons[i]._button, p->_toChange.value());
                std::get<1>(p->_toChangeUI.value()).get().setImage(_window->driver->getTexture(PresetComponent::EquivalentButtons[i]._filename.c_str()));
                p->_callerID = -1;
                p->_toChangeUI.reset();
                p->_toChange.reset();
                break;
            }
        }
    }
}

void PresetSystem::stop()
{
}

void PresetSystem::onTearDown()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &components = _componentManager->getComponentsByType(typeid(PresetComponent).hash_code());

    for (auto &preset : components) {
        auto *p = static_cast<PresetComponent *>(preset.get());
        p->_imagePreset.clear();
        p->_textPreset.clear();
        p->_buttonPreset.clear();
    }
}


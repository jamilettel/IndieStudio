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

#define JOYSTICK_MAX_AXIS_VALUE 32767.0
#define AXISDEADZONEMIN 0.50

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
        auto *ptr = static_cast<PresetComponent *>(preset.get());
        ptr->_toChange.reset();
        ptr->_toChangeUI.reset();
    }
}

void PresetSystem::update()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &components = _componentManager->getComponentsByType(typeid(PresetComponent).hash_code());
    const auto &alertComponent = std::static_pointer_cast<AlertComponent>(_componentManager->getComponentsByType(typeid(AlertComponent).hash_code())[0]);

    for (auto &preset : components) {
        const auto &p = std::static_pointer_cast<PresetComponent>(preset);

        if (!p->_onSelect)
            continue;
        if (!p->_toChange.has_value())
            break;
        for (int i = 0; PresetComponent::EquivalentKeys[i]._key != EKEY_CODE::KEY_KEY_CODES_COUNT && p->_callerID == -1; i++) {
            if (PresetComponent::EquivalentKeys[i]._key != _eventManager->get().getLastKeyPressed())
                continue;
            if (p->getKeyboardPreset().isBound(PresetComponent::EquivalentKeys[i]._key)) {
                alertComponent->addAlert("Key already Bound.");
                p->_toChangeUI.reset();
                p->_toChange.reset();
                goto end;
            }
            p->getKeyboardPreset().bind(PresetComponent::EquivalentKeys[i]._key, p->_toChange.value());
            std::get<0>(p->_toChangeUI.value()).get().setText(PresetComponent::getEquivalentKey(PresetComponent::EquivalentKeys[i]._key));
            p->_toChangeUI.reset();
            p->_toChange.reset();
            goto end;
        }

        if (_eventManager->get().getLastKeyPressed() != KEY_KEY_CODES_COUNT) {
            alertComponent->addAlert("Key already Bound.");
            p->_toChangeUI.reset();
            p->_toChange.reset();
            goto end;
        }

        for (int i = 0; PresetComponent::EquivalentButtons[i]._button != -9999; i++) {
            if (_eventManager->get().isJoystickButtonPressed(p->_callerID, (PresetComponent::EquivalentButtons[i]._button + 1) * -1)) {
                if (p->getJoystickPreset().isBound(PresetComponent::EquivalentButtons[i]._button)) {
                    alertComponent->addAlert("Key already Bound.");
                    p->_toChangeUI.reset();
                    p->_toChange.reset();
                    goto end;
                }
                p->getJoystickPreset().bind(PresetComponent::EquivalentButtons[i]._button, p->_toChange.value());
                std::get<1>(p->_toChangeUI.value()).get().setImage(_window->driver->getTexture(PresetComponent::EquivalentButtons[i]._filename.c_str()));
                p->_callerID = -1;
                p->_toChangeUI.reset();
                p->_toChange.reset();
                goto end;
            }

            if (PresetComponent::EquivalentButtons[i]._button < 0)
                continue;

            s16 axis = _eventManager->get().getAxisValue(p->_callerID, PresetComponent::EquivalentButtons[i]._button);
            float value = static_cast<float>(axis) / JOYSTICK_MAX_AXIS_VALUE;

            if ((PresetComponent::EquivalentButtons[i]._button == 2 || PresetComponent::EquivalentButtons[i]._button == 5) && axis == -JOYSTICK_MAX_AXIS_VALUE)
                continue;

            if (!((value >= 0 && value <= AXISDEADZONEMIN) || (value < 0 && value >= -AXISDEADZONEMIN))) {
                if (p->getJoystickPreset().isBound(PresetComponent::EquivalentButtons[i]._button)) {
                    alertComponent->addAlert("Key already Bound.");
                    p->_toChangeUI.reset();
                    p->_toChange.reset();
                    goto end;
                }
                if (PresetComponent::EquivalentButtons[i]._button == 2 || PresetComponent::EquivalentButtons[i]._button == 5)
                    p->getJoystickPreset().bind(PresetComponent::EquivalentButtons[i]._button, p->_toChange.value());
                else
                    p->getJoystickPreset().bindAxis(PresetComponent::EquivalentButtons[i]._button, p->_toChange.value());
                std::get<1>(p->_toChangeUI.value()).get().setImage(_window->driver->getTexture(PresetComponent::EquivalentButtons[i]._filename.c_str()));
                reloadPresetAxes(p);
                p->_callerID = -1;
                p->_toChangeUI.reset();
                p->_toChange.reset();
                goto end;
            }
        }
        break;
    }
    end:
    _eventManager->get().resetLastKeyPressed();
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

void PresetSystem::reloadPresetAxes(const std::shared_ptr<is::components::PresetComponent> &p)
{
    for (int i = 0; CharacterComponent::playerActions[i].value != -9999; i++) {

        //verif
        auto &image = p->_imagePreset[i];

        image.get().setImage(_window->driver->getTexture(PresetComponent::getEquivalentButton(p->getJoystickPreset().getBindings().at(CharacterComponent::playerActions[i])).c_str()));

    }
}


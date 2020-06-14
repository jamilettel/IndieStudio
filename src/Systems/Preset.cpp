/*
** EPITECH PROJECT, 2020
** Systems/ParticuleSystem.cpp
** File description:
** a
*/

#include "Systems/Preset.hpp"
#include "Components/Preset.hpp"

using namespace is::systems;
using namespace is::components;

#define JOYSTICK_MAX_AXIS_VALUE_PRESET 32767.0
#define AXISDEADZONEMIN 0.50

void PresetSystem::awake()
{
    const auto &windows = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());

    if (windows.empty())
        throw is::exceptions::Exception(
            "Component missing",
            "Window component required for Keyboard Input System");
    const auto &window = std::static_pointer_cast<WindowComponent>(windows[0]);
    _eventManager.emplace(window->eventManager);
    _joysticks = window->joysticks;
    _window = window;
}

void PresetSystem::start()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &components = _componentManager->getComponentsByType(typeid(PresetComponent).hash_code());

    if (components.empty())
        return;
    _eventManager->get().resetLastKeyPressed();
    const auto &p = static_cast<PresetComponent*>(components[0].get());
    p->_onSelect = true;

    for (const auto &preset : components) {
        const auto &ptr = static_cast<PresetComponent*>(preset.get());
        ptr->_toChange.reset();
        ptr->_toChangeUI.reset();
    }
}

void PresetSystem::update()
{
    const auto &components = _componentManager->getComponentsByType(typeid(PresetComponent).hash_code());
    if (components.empty())
        return;

    const auto &alertComponent = static_cast<AlertComponent*>(_componentManager->getComponentsByType(typeid(AlertComponent).hash_code())[0].get());

    for (const auto &preset : components) {
        const auto &p = std::static_pointer_cast<PresetComponent>(preset);

        if (!p->_onSelect)
            continue;
        if (!p->_toChange.has_value())
            break;
        for (int i = 0; PresetComponent::EquivalentKeys[i]._key != irr::EKEY_CODE::KEY_KEY_CODES_COUNT && p->_callerID == -1; i++) {
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

        if (_eventManager->get().getLastKeyPressed() != irr::KEY_KEY_CODES_COUNT) {
            alertComponent->addAlert("Unknown Key.");
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
                std::get<1>(p->_toChangeUI.value()).get().setImage(static_cast<irr::video::ITexture *>(is::Game::getResource(PresetComponent::EquivalentButtons[i]._filename)));
                p->_callerID = -1;
                p->_toChangeUI.reset();
                p->_toChange.reset();
                goto end;
            }

            if (PresetComponent::EquivalentButtons[i]._button < 0)
                continue;

            irr::s16 axis = _eventManager->get().getAxisValue(p->_callerID, PresetComponent::EquivalentButtons[i]._button);
            float value = static_cast<float>(axis) / JOYSTICK_MAX_AXIS_VALUE_PRESET;

            if ((PresetComponent::EquivalentButtons[i]._button == 2 || PresetComponent::EquivalentButtons[i]._button == 5) && axis == -JOYSTICK_MAX_AXIS_VALUE_PRESET)
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
                std::get<1>(p->_toChangeUI.value()).get().setImage(static_cast<irr::video::ITexture *>(is::Game::getResource(PresetComponent::EquivalentButtons[i]._filename)));
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
    auto &components = _componentManager->getComponentsByType(typeid(PresetComponent).hash_code());
    PresetLoader loader;

    for (auto &preset: components) {
        auto ptr = static_cast<PresetComponent *>(preset.get());

        loader.savePreset(*ptr);
    }
    loader.write();
}

void PresetSystem::onTearDown()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &components = _componentManager->getComponentsByType(typeid(PresetComponent).hash_code());

    for (auto &preset : components) {
        const auto &p = std::static_pointer_cast<PresetComponent>(preset);
        p->_imagePreset.clear();
        p->_textPreset.clear();
        p->_buttonPreset.clear();
    }
}

void PresetSystem::reloadPresetAxes(const std::shared_ptr<is::components::PresetComponent> &p)
{
    for (size_t i = 0; CharacterComponent::playerActions[i].value != -9999; i++) {

        if (p->_imagePreset.size() <= i)
            return;

        auto &image = p->_imagePreset[i];
        image.get().setImage(static_cast<irr::video::ITexture *>(is::Game::getResource((PresetComponent::getEquivalentButton(p->getJoystickPreset().getBindings().at(CharacterComponent::playerActions[i]))))));

    }
}


/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** KeyboardInputComponent
*/

#include "Components/KeyboardInput.hpp"

using namespace is::components;
using namespace is::ecs;

KeyboardInputComponent::KeyboardInputComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    InputManagerComponent &inputManager
    ):
    Component(e),
    _inputManager(inputManager)
{
}

void KeyboardInputComponent::deleteComponent()
{
}

bool KeyboardInputComponent::isBound(irr::EKEY_CODE key) const
{
    return _bindings.count(key) == 1;
}

void KeyboardInputComponent::bind(irr::EKEY_CODE key, const std::string &action, float target)
{
    _bindings[key].first = action;
    _bindings[key].second = target;
    _inputManager.setValue(action, 0);
}

void KeyboardInputComponent::unbind(irr::EKEY_CODE key)
{
    auto it = _bindings.find(key);

    if (it != _bindings.end()) {
        _bindings.erase(it);
    }
}

bool KeyboardInputComponent::changeKey(irr::EKEY_CODE from, irr::EKEY_CODE to)
{
    auto it = _bindings.find(from);

    if (it == _bindings.end() || !isBound(to))
        return false;
    _bindings[to] = it->second;
    _bindings.erase(it);
    return true;
}

bool KeyboardInputComponent::changeTarget(irr::EKEY_CODE key, float target)
{
    auto it = _bindings.find(key);

    if (it == _bindings.end())
        return false;
    it->second.second = target;
    return true;
}

const std::map<irr::EKEY_CODE, std::pair<std::string, float>> &KeyboardInputComponent::getBindings() const
{
    return _bindings;
}

InputManagerComponent &KeyboardInputComponent::getInputManager() const
{
    return _inputManager;
}

void KeyboardInputComponent::unbindAll()
{
    _bindings.clear();
}

void KeyboardInputComponent::setPreset(const KeyboardPresetComponent &preset)
{
    for (auto &binding: preset.getBindings())
        bind(binding.second, binding.first.action, binding.first.value);
}

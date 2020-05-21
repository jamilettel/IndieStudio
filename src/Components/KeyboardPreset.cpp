/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** KeyboardPreset
*/

#include "Components/KeyboardPreset.hpp"

using namespace is;
using namespace is::components;
using namespace is::ecs;

KeyboardPresetComponent::KeyboardPresetComponent(
    std::shared_ptr<Entity> &e
    ):
    Component(e)
{}

void KeyboardPresetComponent::deleteComponent()
{}

bool KeyboardPresetComponent::isBound(EKEY_CODE key) const
{
    for (auto &elem: _bindings)
        if (elem.second == key)
            return true;
    return false;
}

void KeyboardPresetComponent::bind(EKEY_CODE key, const PresetAction &action)
{
    _bindings[action] = key;
}

bool KeyboardPresetComponent::changeKey(EKEY_CODE from, EKEY_CODE to)
{
    if (isBound(to))
        return false;
    auto it = std::find_if(
        _bindings.begin(), _bindings.end(),
        [from] (const std::pair<PresetAction, EKEY_CODE> &pair) {
            if (pair.second == from)
                return true;
            return false;
        });
    if (it == _bindings.end())
        return false;
    it->second = to;
    return true;
}

const std::map<PresetAction, EKEY_CODE> &KeyboardPresetComponent::getBindings() const
{
    return _bindings;
}

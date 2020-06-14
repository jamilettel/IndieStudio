/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** SettingsLoaderSystem
*/

#include "Systems/SettingsLoaderSystem.hpp"
#include "Components/Audio.hpp"
#include "Components/RulesSetting.hpp"
#include "SettingsLoader.hpp"
#include "Utils.hpp"
#include "Game.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void SettingsLoaderSystem::awake()
{
}

void SettingsLoaderSystem::start()
{
    if (is::Game::getCurrentScene() != Scenes::SCENE_SPLASH_SCREEN)
        return;
    SettingsLoader loader;
    std::string value;

    if (!loader.loadFile())
        return;

    if (loader.getValue("VolumeMusic", value) && is::Utils::isValidNum(value))
        AudioComponent::_volumeMusic = std::stoi(value);
    if (loader.getValue("VolumeSound", value) && is::Utils::isValidNum(value))
        AudioComponent::_volumeSound = std::stoi(value);
}

void SettingsLoaderSystem::update()
{}

void SettingsLoaderSystem::stop()
{
    if (is::Game::getPreviousScene() == Scenes::SCENE_SPLASH_SCREEN)
        return;
    SettingsLoader loader;

    loader.setValue("VolumeMusic", std::to_string(AudioComponent::_volumeMusic));
    loader.setValue("VolumeSound", std::to_string(AudioComponent::_volumeSound));

    loader.write();
}

void SettingsLoaderSystem::onTearDown()
{}

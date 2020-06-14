/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** SettingsLoaderSystem
*/

#include "Systems/SettingsLoaderSystem.hpp"
#include "Components/Audio.hpp"
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
    auto &list = _componentManager->getComponentsByType(typeid(RulesComponent).hash_code());
    RulesComponent *ptr = nullptr;
    if (list.size())
        ptr = static_cast<RulesComponent *>(list[0].get());

    if (!loader.loadFile())
        return;

    if (loader.getValue("VolumeMusic", value) && is::Utils::isValidNum(value))
        AudioComponent::_volumeMusic = std::stoi(value);
    if (loader.getValue("VolumeSound", value) && is::Utils::isValidNum(value))
        AudioComponent::_volumeSound = std::stoi(value);
    if (!ptr)
        return;
    if (loader.getValue("PlayersNumber", value) && is::Utils::isValidNum(value))
        ptr->setNumberOfPlayers(std::stoi(value));
    if (loader.getValue("MaxTime", value) && is::Utils::isValidNum(value))
        ptr->setMaxTime(std::stoi(value));
    if (loader.getValue("Seed", value) && is::Utils::isValidNum(value))
        ptr->setSeed(std::stoi(value));
    if (loader.getValue("PowerupFrequency", value) && is::Utils::isValidNum(value))
        ptr->setPowerUpFrequency(std::stoi(value));
    if (loader.getValue("IconAccelerator", value) && (value == "true" || value == "false"))
        ptr->setIconUse(components::RulesComponent::ACCELERATOR, value == "true");
    if (loader.getValue("IconExplosion", value) && (value == "true" || value == "false"))
        ptr->setIconUse(components::RulesComponent::EXPLOSION, value == "true");
    if (loader.getValue("IconBomb", value) && (value == "true" || value == "false"))
        ptr->setIconUse(components::RulesComponent::BOMB, value == "true");
    if (loader.getValue("IconWallPass", value) && (value == "true" || value == "false"))
        ptr->setIconUse(components::RulesComponent::WALL_PASS, value == "true");
}

void SettingsLoaderSystem::update()
{}

void SettingsLoaderSystem::stop()
{
    if (is::Game::getPreviousScene() == Scenes::SCENE_SPLASH_SCREEN)
        return;
    SettingsLoader loader;
    auto &list = _componentManager->getComponentsByType(typeid(RulesComponent).hash_code());
    RulesComponent *ptr = nullptr;
    if (list.size())
        ptr = static_cast<RulesComponent *>(list[0].get());

    loader.setValue("VolumeMusic", std::to_string(AudioComponent::_volumeMusic));
    loader.setValue("VolumeSound", std::to_string(AudioComponent::_volumeSound));
    if (!ptr)
        return;
    loader.setValue("PlayersNumber", std::to_string(ptr->getNumberOfPlayers()));
    loader.setValue("MaxTime", std::to_string(ptr->getMaxTime()));
    loader.setValue("Seed", std::to_string(ptr->getSeed()));
    loader.setValue("PowerupFrequency", std::to_string(ptr->getPowerupFrequency()));
    loader.setValue("IconAccelerator", ptr->useIcon(components::RulesComponent::ACCELERATOR) ? "true" : "false");
    loader.setValue("IconExplosion", ptr->useIcon(components::RulesComponent::EXPLOSION) ? "true" : "false");
    loader.setValue("IconBomb", ptr->useIcon(components::RulesComponent::BOMB) ? "true" : "false");
    loader.setValue("IconWallPass", ptr->useIcon(components::RulesComponent::WALL_PASS) ? "true" : "false");

    loader.write();
}

void SettingsLoaderSystem::onTearDown()
{}

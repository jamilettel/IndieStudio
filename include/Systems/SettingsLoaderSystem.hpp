/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** SettingsLoaderSystem
*/

#ifndef SETTINGSLOADERSYSTEM_HPP_
#define SETTINGSLOADERSYSTEM_HPP_

#include "ECS/ASystem.hpp"

namespace is::systems {

    class SettingsLoaderSystem: public is::ecs::ASystem {
    public:
        SettingsLoaderSystem() = default;
        ~SettingsLoaderSystem() = default;

        SettingsLoaderSystem(const SettingsLoaderSystem &) = default;
        SettingsLoaderSystem &operator=(const SettingsLoaderSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

    };

}

#endif

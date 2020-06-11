/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** FireSystem
*/

#include "Systems/Fire.hpp"

using namespace irr;

void is::systems::FireSystem::awake()
{
    auto &entity = initRuntimeEntity(prefabs::GlobalPrefabs::createFireSound(), false);

    _explosionSound.emplace(*entity->getComponent<AudioComponent>()->get());
    _explosionSound->get().init();
    entity->setInit(true);
}

void is::systems::FireSystem::start()
{
    const auto &time = _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code());

    if (time.empty())
        throw is::exceptions::Exception("Fire", "No time component in scene");
    _time.emplace(*static_cast<is::components::TimeComponent *>(time[0].get()));
}

void is::systems::FireSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::FireComponent).hash_code())) {
        const auto &ptr = static_cast<is::components::FireComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("FireComponent", "Could not get FireComponent pointer");
        ptr->lifeTime -= _time->get().getCurrentIntervalSeconds();
        if (ptr->lifeTime < 0) {
            ptr->getEntity()->setDelete(true);
        }
        if (ptr->shouldPlaySound) {
            _explosionSound->get().toPlay();
            ptr->shouldPlaySound = false;
        }
    }
}

void is::systems::FireSystem::stop()
{
}

void is::systems::FireSystem::onTearDown()
{
}


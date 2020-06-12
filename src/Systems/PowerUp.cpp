/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** PowerUpSystem
*/

#include "Systems/PowerUp.hpp"

using namespace irr;
using namespace is::components;

void is::systems::PowerUpSystem::awake()
{
    auto &entity = initRuntimeEntity(prefabs::GlobalPrefabs::createPowerupSound(), false);

    _powerupSound.emplace(*entity->getComponent<AudioComponent>()->get());
    _powerupSound->get().init();
    entity->setInit(true);
}

void is::systems::PowerUpSystem::start()
{

}

void is::systems::PowerUpSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::PowerUpComponent).hash_code())) {
        const auto &ptr = *static_cast<is::components::PowerUpComponent*>(elem.get());

        const auto &componentList = _componentManager->getComponentsByType(typeid(WindowComponent).hash_code());
        const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [&ptr](const std::shared_ptr<is::ecs::Component> &it){
            const auto &p = static_cast<is::components::WindowComponent*>(it.get());
            return p->windowName == ptr.getEntity()->getComponent<ModelRendererComponent>()->get()->windowName;
        });
        if (ptr_window == componentList.end())
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not find window");

        auto window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

        const auto &cc = static_cast<is::components::ColliderComponent*>(ptr.getEntity()->getComponent<is::components::ColliderComponent>()->get());
        checkPowerUpCollision(*cc, window, ptr.type, ptr);
    }
}

void is::systems::PowerUpSystem::checkPowerUpCollision(is::components::ColliderComponent &trcollider,
    const std::shared_ptr<is::components::WindowComponent>& ptr_window,
    is::components::PowerUpComponent::PowerUpType type, const is::components::PowerUpComponent &power)
{
    const auto &colliders = _componentManager->getComponentsByType(typeid(is::components::ColliderComponent).hash_code());

    is::systems::ColliderSystem::precomputeCollisionVariables(trcollider);
    for (const auto &collider : colliders) {
        const auto &ptr = static_cast<is::components::ColliderComponent *>(collider.get());

        if (&trcollider == ptr || !trcollider.collidesWith(ptr->getEntity()->layer))
            continue;
        is::systems::ColliderSystem::precomputeCollisionVariables(*ptr);
        if (is::systems::ColliderSystem::checkCollision(trcollider, *ptr)) {
            auto bm = ptr->getEntity()->getComponent<is::components::BombermanComponent>();
            if (!bm)
                throw is::exceptions::Exception("PowerUpSystem", "Could not find bomberman");
            bm->get()->getCharacter().setNbBonusCollected(bm->get()->getCharacter().getNbBonusCollected() + 1);
            _powerupSound.value().get().toPlay();
            switch (type) {
            case is::components::PowerUpComponent::BOMB_UP:
                bm->get()->bombNumber++;
                break;
            case is::components::PowerUpComponent::SPEED_UP:
                bm->get()->speedMult += 0.5;
                bm->get()->speedCount++;
                break;
            case is::components::PowerUpComponent::FIRE_UP:
                bm->get()->bombRange++;
                break;
            case is::components::PowerUpComponent::WALL_PASS:
                bm->get()->wallPass = true;
                ptr->getEntity()->getComponent<is::components::ColliderComponent>()->get()->removeCollisionWithLayer(is::ecs::Entity::BRKBL_BLK);
                break;
            }
            auto network = _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code());

            if (!network.empty()) {
                const auto &nw = static_cast<is::components::NetworkComponent*>(network[0].get());
                nw->writeQueue.push("evt gpu " + std::to_string(nw->lobby) +
                    " " + std::to_string(nw->playerIdx) + " " + std::to_string(type) + " \n");
            }
            trcollider.getEntity()->setDelete(true);
            return;
        }
    }
}

void is::systems::PowerUpSystem::stop()
{

}

void is::systems::PowerUpSystem::onTearDown()
{

}


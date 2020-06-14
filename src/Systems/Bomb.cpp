/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** BombSystem
*/

#include "Systems/Bomb.hpp"

#include <utility>
#include <cmath>

using namespace irr;
using namespace is::components;

void is::systems::BombSystem::awake()
{
    auto &entity = initRuntimeEntity(prefabs::GlobalPrefabs::createSound("sounds/death.ogg"), false);

    _deathSound.emplace(*entity->getComponent<AudioComponent>()->get());
    _deathSound->get().init();
    entity->setInit(true);
    
    auto &entityFuse = initRuntimeEntity(prefabs::GlobalPrefabs::createSound("sounds/Fuse.ogg"), false);

    _fuseSound.emplace(*entityFuse->getComponent<AudioComponent>()->get());
    _fuseSound->get().init();
    entityFuse->setInit(true);
}

void is::systems::BombSystem::start()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &time =
        _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code());

    if (time.empty())
        throw is::exceptions::Exception("Bomb", "No time component in scene");
    _time.emplace(*static_cast<is::components::TimeComponent *>(time[0].get()));
}

void is::systems::BombSystem::update()
{
    static float angle = 0;
    static int nbBomb = 0;

    int i = 0;
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::BombComponent).hash_code())) {
        const auto &ptr = std::static_pointer_cast<is::components::BombComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("BombComponent", "Could not get BombComponent pointer");
        ptr->lifeTime -= _time->get().getCurrentIntervalSeconds();
        if (ptr->lifeTime < 0) {
            const auto &componentList = _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code());
            const auto &ptr_window = std::find_if(componentList.begin(), componentList.end(), [ptr](const std::shared_ptr<is::ecs::Component> &it){
                const auto &p = static_cast<is::components::WindowComponent*>(it.get());
                return p->windowName == ptr->getEntity()->getComponent<is::components::ModelRendererComponent>()->get()->windowName;
            });
            if (ptr_window == componentList.end())
                throw is::exceptions::Exception("BombComponent", "Could not find window");

            const auto &window = std::static_pointer_cast<is::components::WindowComponent>(*ptr_window);

            for (int i = 0; i < ptr->bombSize && dropFire(ptr, window, 0, i + 1, ptr->getCharacterController()); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, window, i + 1, 0, ptr->getCharacterController()); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, window, 0, -(i + 1), ptr->getCharacterController()); i++);
            for (int i = 0; i < ptr->bombSize && dropFire(ptr, window, -(i + 1), 0, ptr->getCharacterController()); i++);
            dropFire(ptr, window, 0, 0, ptr->getCharacterController());
            ptr->bomberman->instantBomb--;
            ptr->getEntity()->setDelete(true);
        }
        const auto &transform = ptr->getEntity()->getComponent<is::components::TransformComponent>();
        transform->get()->scaleObject(irr::core::vector3df(10+sin(angle * 3.1415 / 180 * 10))); 
        i++;
    }
    angle = (angle >= 360 ? 0 : angle + 1);
    if (i == 0) {
        _fuseSound.value().get().toStop();
    } else {
        if (i > nbBomb || !_fuseSound.value().get().isPlaying()) {
            _fuseSound.value().get().toPlay();
        }
    }
    nbBomb = i;
}

bool is::systems::BombSystem::dropFire(const std::shared_ptr<is::components::BombComponent> &ptr,
                                       const std::shared_ptr<is::components::WindowComponent> &ptr_window,
                                       int x,
                                       int y,
                                       CharacterControllerComponent &ch)
{
    irr::core::vector3df f = ptr->getEntity()->getComponent<is::components::TransformComponent>()->get()->position;

    f.X = ((int)((f.X + 1.5f) / 3) + x - (f.X < 0)) * 3;
    f.Y = 0;
    f.Z = ((int)((f.Z + 1.5f) / 3) + y - (f.Z < 0)) * 3;

    auto e = this->initRuntimeEntity(is::prefabs::GlobalPrefabs::createFire(f));
    const auto &part = static_cast<is::components::ParticuleComponent*>(e->getComponent<is::components::ParticuleComponent>()->get());

    part->init(ptr_window);

    const auto &cc = static_cast<is::components::ColliderComponent*>(e->getComponent<is::components::ColliderComponent>()->get());

    if (checkFireCollision(*cc, ptr_window, ch)) {
        e->setDelete(true);
        return (false);
    }
    return (true);
}


bool is::systems::BombSystem::checkFireCollision(
    is::components::ColliderComponent &trcollider,
    const std::shared_ptr<is::components::WindowComponent>& ptr_window,
    CharacterControllerComponent &ch
)
{
    std::vector<std::shared_ptr<is::ecs::Component>> &colliders =
    _componentManager->getComponentsByType(typeid(is::components::ColliderComponent).hash_code());

    is::systems::ColliderSystem::precomputeCollisionVariables(trcollider);
    for (const auto &collider : colliders) {
        const auto &ptr = static_cast<is::components::ColliderComponent *>(collider.get());

        if (&trcollider == ptr || (!trcollider.collidesWith(ptr->getEntity()->layer) && ptr->getEntity()->layer != is::ecs::Entity::BRKBL_BLK && ptr->getEntity()->layer != is::ecs::Entity::PLAYER))
            continue;
        is::systems::ColliderSystem::precomputeCollisionVariables(*ptr);
        if (is::systems::ColliderSystem::checkCollision(trcollider, *ptr)) {
            if (ptr->getEntity()->layer == is::ecs::Entity::BRKBL_BLK) {
                ptr->getEntity()->setDelete(true);
                auto network = _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code());

                if (network.empty())
                    generateRandomPowerUp(ptr, ptr_window);
                else {
                    const auto &nw = static_cast<is::components::NetworkComponent*>(network[0].get());
                    if (nw->playerIdx == 0) {
                        int idx = generateRandomPowerUp(ptr, ptr_window);
                        if (idx) {
                            nw->writeQueue.push("evt pu " + std::to_string(nw->lobby) +
                                                " " + std::to_string(nw->playerIdx) + " " + std::to_string(idx) +
                                                " " + std::to_string(ptr->getTransform().position.X) +
                                                " " + std::to_string(ptr->getTransform().position.Z) + " \n");
                        }
                    }
                }
            }
            if (ptr->getEntity()->layer == is::ecs::Entity::PLAYER) {
                auto &bmEnemy = *ptr->getEntity()->getComponent<is::components::BombermanComponent>()->get();
                if (!bmEnemy.dead) {
                    ch.getCharacterComponent().setNbCharactersKilled(ch.getCharacterComponent().getNbCharactersKilled() + 1);
                    _deathSound.value().get().toPlay();
                }
                bmEnemy.dead = true;
                continue;
            }
            return (true);
        }
    }
    return (false);
}

int is::systems::BombSystem::generateRandomPowerUp(is::components::ColliderComponent *ptr_cc,
    const std::shared_ptr<is::components::WindowComponent> &ptr_window)
{
    auto rulesComponents = _componentManager->getComponentsByType(typeid(is::components::RulesComponent).hash_code());
    auto rules = static_cast<is::components::RulesComponent*>(rulesComponents[0].get());

    if (!rules->getNbIcons())
        return (0);
    int i = std::rand() % rules->getNbIcons();
    int fq = 11 - rules->getPowerupFrequency();
    if (fq > 10 || fq < 0)
        return (0);
    if (std::rand() % fq != 0)
        return (0);
    std::shared_ptr<is::ecs::Entity> e;

    if (rules->getIcon(i) == rules->BOMB && rules->useIcon(rules->BOMB))
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createBombUpPowerUp(ptr_cc->getTransform().position));
    else if (rules->getIcon(i) == rules->ACCELERATOR && rules->useIcon(rules->ACCELERATOR))
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createSpeedUpPowerUp(ptr_cc->getTransform().position));
    else if (rules->getIcon(i) == rules->EXPLOSION && rules->useIcon(rules->EXPLOSION))
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createFireUpPowerUp(ptr_cc->getTransform().position));
    else if (rules->getIcon(i) == rules->WALL_PASS && rules->useIcon(rules->WALL_PASS))
        e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createWallPassPowerUp(ptr_cc->getTransform().position));
    else
        return (0);
    auto ptr = static_cast<is::components::ModelRendererComponent*>(e->getComponent<is::components::ModelRendererComponent>()->get());
    ptr->initModelRenderer(ptr_window);
    return (i + 1);
}

void is::systems::BombSystem::stop()
{

}

void is::systems::BombSystem::onTearDown()
{

}


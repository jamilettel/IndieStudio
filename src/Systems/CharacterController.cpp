/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CharacterControllerSystem
*/

#include "Systems/CharacterController.hpp"
#include "Components/Audio.hpp"

using namespace irr;
using namespace is::components;

void is::systems::CharacterControllerSystem::awake()
{
    auto &entity = initRuntimeEntity(prefabs::GlobalPrefabs::createbombsetSound(), false);

    _bombsetSound.emplace(*entity->getComponent<AudioComponent>()->get());
    _bombsetSound->get().init();
    entity->setInit(true);
}

void is::systems::CharacterControllerSystem::start()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(CharacterControllerComponent).hash_code())) {
        const auto &ptr = static_cast<CharacterControllerComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not get CharacterControllerComponent pointer");
        if (elem->getEntity()->isInit())
            continue;
        auto im = ptr->getEntity()->getComponent<is::components::InputManagerComponent>();
        if (!im)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not found bomberman");
    }
    std::vector<std::shared_ptr<is::ecs::Component>> &time =
        _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());

    if (!time.size())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<TimeComponent*>(time[0].get()));
}

void is::systems::CharacterControllerSystem::rotateToAngle(irr::core::vector3df &rotate,
                                                           float angle)
{
    int diff;

    angle = 360 - angle;
    diff = (360 + (int)angle - (int)rotate.Y) % 360;
    if (diff > 180)
        rotate.Y += 15;
    else if (diff < 180)
        rotate.Y -= 15;
}

void is::systems::CharacterControllerSystem::rotateToDirection(irr::core::vector3df move,
                                                               irr::core::vector3df &rotate)
{
    float angle;

    if (move.X == 0 && move.Z == 0)
        return;
    if (move.X < 0)
        angle = 270 - (atan(move.Z / -move.X) * 180 / M_PI);
    else
        angle = 90 + (atan(move.Z / move.X) * 180 / M_PI);
    rotateToAngle(rotate, angle);
}

void is::systems::CharacterControllerSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(CharacterControllerComponent).hash_code())) {
        const auto &ptr = static_cast<CharacterControllerComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not get CharacterControllerComponent pointer");
        if (ptr->isDead)
            continue;
        ptr->getCharacterComponent().udpateTime();
        auto bm = ptr->getEntity()->getComponent<is::components::BombermanComponent>();
        if (!bm)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not found bomberman");
        if (bm->get()->dead && !ptr->isDead) {
            bm->get()->deathTimer -= _time->get().getCurrentIntervalSeconds();
            if (bm->get()->deathTimer <= 0) {
                ptr->isDead = true;
                ptr->getEntity()->getComponent<ModelRendererComponent>().value()->deleteComponent();
            }
            ptr->getEntity()->getComponent<is::components::AnimatorComponent>()->get()->changeAnimation("Death", false);
            continue;
        }
        const auto im = ptr->getEntity()->getComponent<is::components::InputManagerComponent>();
        if (!im)
            throw is::exceptions::Exception("CharacterControllerSystem", "Could not found bomberman");
        ptr->move.X = im->get()->getInput("MoveVerticalAxis");
        ptr->move.Z = im->get()->getInput("MoveHorizontalAxis");
        ptr->dropBombFrame = false;
        if (im->get()->getInput("DropBomb") == 1 && ptr->canPlaceBomb) {
            if (bm->get()->instantBomb + 1 <= bm->get()->bombNumber) {
                ptr->dropBombFrame = true;

                const auto &windows = _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code());
                const auto &window = std::find_if(windows.begin(), windows.end(), [ptr](const std::shared_ptr<is::ecs::Component> &it){
                    const auto &p = static_cast<is::components::WindowComponent*>(it.get());
                    return p->windowName == ptr->getEntity()->getComponent<is::components::ModelRendererComponent>()->get()->windowName;
                });
                if (window == windows.end())
                    throw is::exceptions::Exception("CharacterControllerSystem", "Could not find window");

                const auto &w = std::static_pointer_cast<is::components::WindowComponent>(*window);

                bm->get()->instantBomb++;
                ptr->getCharacterComponent().setNbBombPosed(ptr->getCharacterComponent().getNbBombPosed() + 1);
                auto e = this->initRuntimeEntity(prefabs::GlobalPrefabs::createBomb(ptr->getTransform().position, bm->get()->bombRange, bm.value(), *ptr));
                const auto &ptr_mr = static_cast<ModelRendererComponent*>(e->getComponent<ModelRendererComponent>()->get());
                const auto &ptr_part = static_cast<ParticuleComponent*>(e->getComponent<ParticuleComponent>()->get());
                ptr_mr->initModelRenderer(w);
                ptr_part->init(w);
                ptr->canPlaceBomb = false;
                _bombsetSound.value().get().toPlay();
            }
        } else if (im->get()->getInput("DropBomb") != 1 && ptr->getTransform().position != ptr->lastPos) {
            ptr->canPlaceBomb = true;
        }
        ptr->getMovementComponent().velocity = ptr->move * ptr->playerSpeed * bm->get()->speedMult;
        rotateToDirection(ptr->move, ptr->getTransform().rotation);
        if (ptr->getTransform().position != ptr->lastPos) {
            if (ptr->shouldPlayFootstepSound(_time->get().getCurrentIntervalSeconds()))
                ptr->getAudioComponent().toPlay();
            ptr->getEntity()->getComponent<is::components::AnimatorComponent>()->get()->changeAnimation("Walk");
        }
        else if (ptr->canPlaceBomb)
            ptr->getEntity()->getComponent<is::components::AnimatorComponent>()->get()->changeAnimation("Idle");
        else {
            ptr->dropBombTimer += _time->get().getCurrentIntervalSeconds();
            ptr->getEntity()->getComponent<is::components::AnimatorComponent>()->get()->changeAnimation("DropBomb");
            if (ptr->dropBombTimer > 0.5f) {
                ptr->dropBombTimer = 0.0f;
                ptr->canPlaceBomb = true;
            }
        }
        ptr->lastPos = ptr->getTransform().position;
    }
}

void is::systems::CharacterControllerSystem::stop()
{
}

void is::systems::CharacterControllerSystem::onTearDown()
{
}

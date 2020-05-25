/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#include "Prefabs/GlobalPrefabs.hpp"
#include "Game.hpp"
#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

using namespace is::ecs;
using namespace is::components;
using namespace is::prefabs;

std::shared_ptr<Entity> GlobalPrefabs::createWallBlock(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::GROUND);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("cubb.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createCenterBlock(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::GROUND);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("poteau.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createGrassBlock(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::GROUND);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("grass.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createBreakableBlock(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::BRKBL_BLK);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("crate.obj"), "Indie Studio");
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createBomb(irr::core::vector3df position,
    int range,
    std::shared_ptr<is::components::BombermanComponent> &bm)
{
    auto e = std::make_shared<Entity>(Entity::BOMB);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("bomb.obj"), "Indie Studio");
    e->addComponent<BombComponent>(e, bm, 3, range);
    e->addComponent<is::components::ParticuleComponent>(
        e,
        "Indie Studio",
        irr::core::vector3df(position.X, position.Y + 3, position.Z),
        PARTICULE::WICK
    );
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createBombUpPowerUp(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::POWERUP);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("powerup.b3d"), "Indie Studio", RESSOURCE("bombup.png"));
    e->addComponent<PowerUpComponent>(e, PowerUpComponent::PowerUpType::BOMB_UP);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(Entity::PLAYER);
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createSpeedUpPowerUp(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::POWERUP);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("powerup.b3d"), "Indie Studio", RESSOURCE("speedup.png"));
    e->addComponent<PowerUpComponent>(e, PowerUpComponent::PowerUpType::SPEED_UP);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(Entity::PLAYER);
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createFireUpPowerUp(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::POWERUP);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("powerup.b3d"), "Indie Studio", RESSOURCE("fireup.png"));
    e->addComponent<PowerUpComponent>(e, PowerUpComponent::PowerUpType::FIRE_UP);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(Entity::PLAYER);
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createWallPassPowerUp(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::POWERUP);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("powerup.b3d"), "Indie Studio", RESSOURCE("wallpass.png"));
    e->addComponent<PowerUpComponent>(e, PowerUpComponent::PowerUpType::WALL_PASS);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    collider.addCollisionWithLayer(Entity::PLAYER);
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createFire(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::FIRE);

    TransformComponent &transform = e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(3, 3, 3));
    //e->addComponent<ModelRendererComponent>(e, RESSOURCE("Prop_Block_Pause.obj"), "Indie Studio");
    e->addComponent<FireComponent>(e);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<is::components::ParticuleComponent>(
        e,
        "Indie Studio",
        irr::core::vector3df(position.X, position.Y + 3, position.Z),
        PARTICULE::FIRE
    );
    collider.addCollisionWithLayer(Entity::GROUND);
    collider.addCollisionWithLayer(Entity::BOMB);
    collider.addCollisionWithLayer(Entity::FIRE);
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createBombermanCharacter(
    const irr::core::vector3df &pos,
    is::components::CharacterComponent &character,
    const is::ecs::ComponentManager &manager
)
{
    auto e = createBomberman(pos, character);
    InputManagerComponent &input = e->addComponent<InputManagerComponent>(e);

    switch (character.characterType) {
    case CharacterComponent::AI: {
        e->addComponent<AIControllerComponent>(e, input);
        break;
    } case CharacterComponent::JOYSTICK_PLAYER: {
        const auto &presets = manager.getComponentsByType(typeid(PresetComponent).hash_code());
        const auto it = std::find_if(
            presets.begin(), presets.end(),
            [&character] (const std::shared_ptr<is::ecs::Component> &component) {
                const auto *preset = static_cast<PresetComponent *>(component.get());

                return preset->presetNumber == character.presetNumber;
            });
        if (it == presets.end())
            throw is::exceptions::Exception("Character", "Unable to find preset in components");
        JoystickInputComponent &joystick = e->addComponent<JoystickInputComponent>(e, input);
        joystick.assignJoystick(character.joystickId);
        joystick.setPreset(static_cast<PresetComponent *>(it->get())->getJoystickPreset());
        break;
    } case CharacterComponent::KEYBOARD_PLAYER: {
        const auto &presets = manager.getComponentsByType(typeid(PresetComponent).hash_code());
        const auto it = std::find_if(
            presets.begin(), presets.end(),
            [&character] (const std::shared_ptr<is::ecs::Component> &component) {
                const auto *preset = static_cast<PresetComponent *>(component.get());

                return preset->presetNumber == character.presetNumber;
            });
        if (it == presets.end())
            throw is::exceptions::Exception("Character", "Unable to find preset in components");
        KeyboardInputComponent &keyboard = e->addComponent<KeyboardInputComponent>(e, input);
        keyboard.setPreset(static_cast<PresetComponent *>(it->get())->getKeyboardPreset());
        break;
      }
    }
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createBomberman(const irr::core::vector3df &pos, CharacterComponent &character)
{
    auto e = std::make_shared<Entity>(Entity::PLAYER);

    TransformComponent &transform = e->addComponent<TransformComponent>(
        e,
        pos,
        irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(0.7f)
        );
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(2, 2, 2)
    );
    MovementComponent &movement = e->addComponent<MovementComponent>(
        e,
        transform,
        collider
    );
    AudioComponent &audio = e->addComponent<is::components::AudioComponent>(
        e,
        RESSOURCE("footstep.wav"),
        is::components::SOUND
    );
    AnimatorComponent &animator = e->addComponent<is::components::AnimatorComponent>(e);
    character.reset();
    e->addComponent<CharacterControllerComponent>(
        e,
        transform,
        movement,
        audio,
        character,
        "Indie Studio",
        0.1
    );
    collider.addCollisionWithLayer(Entity::GROUND);
    collider.addCollisionWithLayer(Entity::BRKBL_BLK);
    e->addComponent<ModelRendererComponent>(e, RESSOURCE("player.b3d"), "Indie Studio");
    e->addComponent<GravityComponent>(e, movement);
    transform.position.Y = 10;
    e->addComponent<BombermanComponent>(e);
    e->addComponent<JumpComponent>(e, movement);
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createCharacter()
{
    auto e = std::make_shared<is::ecs::Entity>();

    e->addComponent<CharacterComponent>(e, 0);
    e->addComponent<CharacterComponent>(e, 1);
    e->addComponent<CharacterComponent>(e, 2);
    e->addComponent<CharacterComponent>(e, 3);
    return e;
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createPresets()
{
    auto e = std::make_shared<is::ecs::Entity>();

    auto &preset1 = e->addComponent<PresetComponent>(e, 1);
    auto &preset2 = e->addComponent<PresetComponent>(e, 2);
    auto &preset3 = e->addComponent<PresetComponent>(e, 3);
    auto &preset4 = e->addComponent<PresetComponent>(e, 4);

    is::components::KeyboardPresetComponent::createBasicPreset(preset1.getKeyboardPreset());
    is::components::KeyboardPresetComponent::createBasicPreset(preset2.getKeyboardPreset());
    is::components::KeyboardPresetComponent::createBasicPreset(preset3.getKeyboardPreset());
    is::components::KeyboardPresetComponent::createBasicPreset(preset4.getKeyboardPreset());

    return e;
}

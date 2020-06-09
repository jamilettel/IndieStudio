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
using namespace is::prefabs;
using namespace is::components;

std::shared_ptr<Entity> GlobalPrefabs::createWallBlock(const irr::core::vector3df &position)
{
    auto e = std::make_shared<Entity>(Entity::GROUND);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(1.5f));
    e->addComponent<ColliderComponent>(
        e,
        *e->getComponent<TransformComponent>()->get(),
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ModelRendererComponent>(e, "cubb.obj", "Indie Studio");
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
    e->addComponent<ModelRendererComponent>(e, "poteau.obj", "Indie Studio");
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
    e->addComponent<ModelRendererComponent>(e, "grass.obj", "Indie Studio");
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
    e->addComponent<ModelRendererComponent>(e, "crate.obj", "Indie Studio");
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createBomb(
    irr::core::vector3df position,
    int range,
    std::shared_ptr<BombermanComponent> &bm,
    CharacterControllerComponent &ch
)
{
    auto e = std::make_shared<Entity>(Entity::BOMB);

    e->addComponent<TransformComponent>(e, position, irr::core::vector3df(0, 0, 0), irr::core::vector3df(10, 10, 10));
    e->addComponent<ModelRendererComponent>(e, "bomb.obj", "Indie Studio");
    e->addComponent<BombComponent>(e, bm, position, ch, 3, range);
    
    e->addComponent<ParticuleComponent>(
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
    e->addComponent<ModelRendererComponent>(e, "powerup.b3d", "Indie Studio", "bombup.png");
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
    e->addComponent<ModelRendererComponent>(e, "powerup.b3d", "Indie Studio", "speedup.png");
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
    e->addComponent<ModelRendererComponent>(e, "powerup.b3d", "Indie Studio", "fireup.png");
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
    e->addComponent<ModelRendererComponent>(e, "powerup.b3d", "Indie Studio", "wallpass.png");
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
    e->addComponent<FireComponent>(e);
    ColliderComponent &collider = e->addComponent<ColliderComponent>(
        e,
        transform,
        irr::core::vector3df(3, 3, 3)
    );
    e->addComponent<ParticuleComponent>(
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
    CharacterComponent &character,
    const ComponentManager &manager,
    const std::string &texture,
    int level
    )
{
    auto e = createBomberman(pos, character, texture);
    InputManagerComponent &input = e->addComponent<InputManagerComponent>(e);

    switch (character.characterType) {
    case CharacterComponent::AI: {
        e->addComponent<AIControllerComponent>(e, input, level);
        break;
    }
    case CharacterComponent::JOYSTICK_PLAYER: {
        const auto &presets = manager.getComponentsByType(typeid(PresetComponent).hash_code());
        const auto it = std::find_if(
            presets.begin(), presets.end(),
            [&character] (const std::shared_ptr<Component> &component) {
                const auto *preset = static_cast<PresetComponent *>(component.get());

                return preset->presetNumber == character.presetNumber;
            });
        if (it == presets.end())
            throw is::exceptions::Exception("Character", "Unable to find preset in components");
        JoystickInputComponent &joystick = e->addComponent<JoystickInputComponent>(e, input);
        joystick.assignJoystick(character.joystickId);
        joystick.setPreset(static_cast<PresetComponent *>(it->get())->getJoystickPreset());
        break;
    }
    case CharacterComponent::KEYBOARD_PLAYER: {
        const auto &presets = manager.getComponentsByType(typeid(PresetComponent).hash_code());
        const auto it = std::find_if(
            presets.begin(), presets.end(),
            [&character] (const std::shared_ptr<Component> &component) {
                const auto *preset = static_cast<PresetComponent *>(component.get());

                return preset->presetNumber == character.presetNumber;
            });
        if (it == presets.end())
            throw is::exceptions::Exception("Character", "Unable to find preset in components");
        KeyboardInputComponent &keyboard = e->addComponent<KeyboardInputComponent>(e, input);
        keyboard.setPreset(static_cast<PresetComponent *>(it->get())->getKeyboardPreset());
        break;
    }
    case CharacterComponent::MULTIPLAYER_PLAYER: {
        e->addComponent<NetworkInputComponent>(e, input, character.multiplayerId);
        break;
    }
    }
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createBomberman(const irr::core::vector3df &pos, CharacterComponent &character, const std::string &texture)
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
    AudioComponent &audio = e->addComponent<AudioComponent>(
        e,
        RESSOURCE("footstep.wav"),
        SOUND
    );
    AnimatorComponent &animator = e->addComponent<AnimatorComponent>(e);
    e->addComponent<CharacterControllerComponent>(
        e,
        transform,
        movement,
        audio,
        character,
        "Indie Studio",
        0.1
    );
    TimeComponent &time = e->addComponent<TimeComponent>(e);
    character.setTimeComponent(time);
    character.reset();
    collider.addCollisionWithLayer(Entity::GROUND);
    collider.addCollisionWithLayer(Entity::BRKBL_BLK);
    e->addComponent<ModelRendererComponent>(e, "player.b3d", "Indie Studio", texture);
    e->addComponent<BombermanComponent>(e, character);
    animator.animators.push_back({0, 25, "Walk"});
    animator.animators.push_back({26, 41, "DropBomb"});
    animator.animators.push_back({41, 60, "Death"});
    animator.animators.push_back({61, 86, "Idle"});
    return (e);
}

std::shared_ptr<Entity> GlobalPrefabs::createCharacter()
{
    auto e = std::make_shared<Entity>();

    e->addComponent<CharacterComponent>(e, 0, "player_white.png");
    e->addComponent<CharacterComponent>(e, 1, "player_black.png");
    e->addComponent<CharacterComponent>(e, 2, "player_blue.png");
    e->addComponent<CharacterComponent>(e, 3, "player_red.png");

    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createPresets()
{
    auto e = std::make_shared<Entity>();

    auto &preset1 = e->addComponent<PresetComponent>(e, 1);
    auto &preset2 = e->addComponent<PresetComponent>(e, 2);
    auto &preset3 = e->addComponent<PresetComponent>(e, 3);
    auto &preset4 = e->addComponent<PresetComponent>(e, 4);

    KeyboardPresetComponent::createBasicPreset(preset1.getKeyboardPreset());
    KeyboardPresetComponent::createBasicPreset(preset2.getKeyboardPreset());
    KeyboardPresetComponent::createBasicPreset(preset3.getKeyboardPreset());
    KeyboardPresetComponent::createBasicPreset(preset4.getKeyboardPreset());

    JoystickPresetComponent::createBasicPreset(preset1.getJoystickPreset());
    JoystickPresetComponent::createBasicPreset(preset2.getJoystickPreset());
    JoystickPresetComponent::createBasicPreset(preset3.getJoystickPreset());
    JoystickPresetComponent::createBasicPreset(preset4.getJoystickPreset());

    return e;
}

std::shared_ptr<Entity> GlobalPrefabs::createRules()
{
    auto e = std::make_shared<Entity>();

    e->addComponent<RulesComponent>(e);
    return (e);
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createTimer(RulesComponent &rules)
{
    auto e = std::make_shared<is::ecs::Entity>();

    TextComponent &text = e->addComponent<TextComponent>(
        e,
        rules.getTimeString(),
        "Indie Studio",
        WindowComponent::_windowsDimensions["Indie Studio"].first / 2 - 950, 5,
        400, 100,
        false,
        true,
        "fonts/fontVolumeSettings/fontVolumeSettings.xml",
        irr::video::SColor(255, 227, 245, 244)
    );
    e->addComponent<TextureComponent>(
        e,
        "ui/Game/Table_02.png",
        "Indie Studio",
        irr::core::vector2df(1, 1),
        irr::core::vector2df(19.8, 10)
    );
    TimeComponent &timeC = e->addComponent<TimeComponent>(
        e
    );
    e->addComponent<TimerComponent>(
        e,
        text,
        timeC,
        rules.getMaxTime()
    );
    return (e);
}

std::shared_ptr<is::ecs::Entity> GlobalPrefabs::createPauseController(const is::components::CharacterComponent &character, is::ecs::ComponentManager &manager)
{
    auto e = std::make_shared<is::ecs::Entity>();
    InputManagerComponent &inputManager = e->addComponent<InputManagerComponent>(e);

    switch (character.characterType) {
    case CharacterComponent::JOYSTICK_PLAYER: {
        const auto &presets = manager.getComponentsByType(typeid(PresetComponent).hash_code());
        const auto it = std::find_if(
            presets.begin(), presets.end(),
            [&character] (const std::shared_ptr<Component> &component) {
                const auto *preset = static_cast<PresetComponent *>(component.get());

                return preset->presetNumber == character.presetNumber;
            });
        if (it == presets.end())
            throw is::exceptions::Exception("Character", "Unable to find preset in components");
        JoystickInputComponent &joystick = e->addComponent<JoystickInputComponent>(e, inputManager);
        joystick.assignJoystick(character.joystickId);
        joystick.setPreset(static_cast<PresetComponent *>(it->get())->getJoystickPreset());
        break;
    }
    case CharacterComponent::KEYBOARD_PLAYER: {
        const auto &presets = manager.getComponentsByType(typeid(PresetComponent).hash_code());
        const auto it = std::find_if(
            presets.begin(), presets.end(),
            [&character] (const std::shared_ptr<Component> &component) {
                const auto *preset = static_cast<PresetComponent *>(component.get());

                return preset->presetNumber == character.presetNumber;
            });
        if (it == presets.end())
            throw is::exceptions::Exception("Character", "Unable to find preset in components");
        KeyboardInputComponent &keyboard = e->addComponent<KeyboardInputComponent>(e, inputManager);
        keyboard.setPreset(static_cast<PresetComponent *>(it->get())->getKeyboardPreset());
        break;
    }
    default:
        break;
    }
    return e;
}

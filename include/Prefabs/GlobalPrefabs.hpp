/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#ifndef GLOBALPREFABS_HPP_
#define GLOBALPREFABS_HPP_

#include <memory>

#include "ECS/Entity.hpp"

#include "Components/Window.hpp"
#include "Components/Camera.hpp"
#include "Components/Transform.hpp"
#include "Components/ModelRenderer.hpp"
#include "Components/CharacterController.hpp"
#include "Components/Light.hpp"
#include "Components/Audio.hpp"
#include "Components/Collider.hpp"
#include "Components/Movement.hpp"
#include "Components/Gravity.hpp"
#include "Components/Bomb.hpp"
#include "Components/Fire.hpp"
#include "Components/Time.hpp"
#include "Components/Button.hpp"
#include "Components/Text.hpp"
#include "Components/Slider.hpp"
#include "Components/Image.hpp"
#include "Components/ColliderTrigger.hpp"
#include "Components/PowerUp.hpp"
#include "Components/Jump.hpp"
#include "Components/InputManager.hpp"
#include "Components/KeyboardInput.hpp"
#include "Components/AIController.hpp"
#include "Components/JoystickInput.hpp"
#include "Components/Animator.hpp"
#include "Components/Particule.hpp"
#include "Components/Cursor.hpp"
#include "Components/Character.hpp"
#include "Components/Preset.hpp"

namespace is::prefabs {

    class GlobalPrefabs {
    public:
        static std::shared_ptr<is::ecs::Entity> createGlobalPrefab();
        static std::shared_ptr<is::ecs::Entity> createWallBlock(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createCenterBlock(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createGrassBlock(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createBomb(irr::core::vector3df position, int range, std::shared_ptr<is::components::BombermanComponent> &bm);
        static std::shared_ptr<is::ecs::Entity> createFire(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createBreakableBlock(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createBombUpPowerUp(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createSpeedUpPowerUp(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createFireUpPowerUp(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createWallPassPowerUp(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createPlayer(irr::core::vector3df pos);
        // static std::shared_ptr<is::ecs::Entity> createPlayer(irr::core::vector3df pos, const is::components::CharacterComponent &character);
        static std::shared_ptr<is::ecs::Entity> createAI(irr::core::vector3df pos);

        static std::shared_ptr<is::ecs::Entity> createSplashScreen();
        static std::shared_ptr<is::ecs::Entity> createMainMenu();
        static std::shared_ptr<is::ecs::Entity> createPause();
        static std::shared_ptr<is::ecs::Entity> createCredit();
        static std::shared_ptr<is::ecs::Entity> createHowToPlay();
        static std::shared_ptr<is::ecs::Entity> createRecord();

        static std::shared_ptr<is::ecs::Entity> createSettings();
        static std::shared_ptr<is::ecs::Entity> createControllers();
        static std::shared_ptr<is::ecs::Entity> createPresetSelectionBase();
        static std::shared_ptr<is::ecs::Entity> createPresetSelectionOptions();

        static std::shared_ptr<is::ecs::Entity> createCharacter();
        static std::shared_ptr<is::ecs::Entity> createPresets();
    };

}

#endif /* !GLOBALPREFABS_HPP_ */

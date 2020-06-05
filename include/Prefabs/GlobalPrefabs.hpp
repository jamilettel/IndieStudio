/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#ifndef GLOBALPREFABS_HPP_
#define GLOBALPREFABS_HPP_

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
#include "Components/NetworkInput.hpp"
#include "Components/AIController.hpp"
#include "Components/JoystickInput.hpp"
#include "Components/Animator.hpp"
#include "Components/Particule.hpp"
#include "Components/Cursor.hpp"
#include "Components/Rules.hpp"
#include "Components/RulesSetting.hpp"
#include "Components/Alert.hpp"
#include "ECS/AScene.hpp"
#include "Components/Character.hpp"
#include "ECS/ComponentManager.hpp"
#include "Components/Preset.hpp"
#include "Components/Network.hpp"
#include "Components/JoystickCursor.hpp"
#include "Components/Texture.hpp"
#include "Components/Timer.hpp"
#include "Components/NumberField.hpp"

namespace is::prefabs {

    class GlobalPrefabs {
    public:
        static std::shared_ptr<is::ecs::Entity> createGlobalPrefab();
        static std::shared_ptr<is::ecs::Entity> createGlobalPrefabMultiplayer();
        static std::shared_ptr<is::ecs::Entity> createWallBlock(const irr::core::vector3df &position);
        static std::shared_ptr<is::ecs::Entity> createCenterBlock(const irr::core::vector3df &position);
        static std::shared_ptr<is::ecs::Entity> createGrassBlock(const irr::core::vector3df &position);
        static std::shared_ptr<is::ecs::Entity> createBomb(irr::core::vector3df position, int range, std::shared_ptr<is::components::BombermanComponent> &bm, is::components::CharacterControllerComponent &ch);
        static std::shared_ptr<is::ecs::Entity> createFire(const irr::core::vector3df &position);
        static std::shared_ptr<is::ecs::Entity> createBreakableBlock(const irr::core::vector3df &position);
        static std::shared_ptr<is::ecs::Entity> createBombUpPowerUp(const irr::core::vector3df &position);
        static std::shared_ptr<is::ecs::Entity> createSpeedUpPowerUp(const irr::core::vector3df &position);
        static std::shared_ptr<is::ecs::Entity> createFireUpPowerUp(const irr::core::vector3df &position);
        static std::shared_ptr<is::ecs::Entity> createWallPassPowerUp(const irr::core::vector3df &position);

        static std::shared_ptr<is::ecs::Entity> createMultiplayer(std::shared_ptr<is::components::NetworkComponent> nc);
        static std::shared_ptr<is::ecs::Entity> createBombermanCharacter(
                const irr::core::vector3df &pos,
                is::components::CharacterComponent &character,
                const is::ecs::ComponentManager &manager,
                const std::string &texture,
                int level = 1
            );

        static std::shared_ptr<is::ecs::Entity> createSplashScreen();
        static std::shared_ptr<is::ecs::Entity> createMainMenu();
        static std::shared_ptr<is::ecs::Entity> createPause();
        static std::shared_ptr<is::ecs::Entity> createCredit();
        static std::shared_ptr<is::ecs::Entity> createHowToPlay();
        static std::shared_ptr<is::ecs::Entity> createRecord();
        static std::shared_ptr<is::ecs::Entity> createEndGame();

        static std::shared_ptr<is::ecs::Entity> createPresetSelection(const is::ecs::ComponentManager &manager);
        static std::shared_ptr<is::ecs::Entity> createPresetSelectionBase(std::shared_ptr<is::ecs::Entity> &e);
        static std::shared_ptr<is::ecs::Entity>
        createPresetSelectionPlayer1(std::shared_ptr<is::ecs::Entity> &e,
                                     const std::shared_ptr<ecs::Component> &player,
                                     const std::shared_ptr<components::RulesComponent> &ruleComponent);
        static std::shared_ptr<is::ecs::Entity>
        createPresetSelectionPlayer2(std::shared_ptr<is::ecs::Entity> &e,
                                     const std::shared_ptr<ecs::Component> &player,
                                     const std::shared_ptr<components::RulesComponent> &ruleComponent);
        static std::shared_ptr<is::ecs::Entity>
        createPresetSelectionPlayer3(std::shared_ptr<is::ecs::Entity> &e,
                                     const std::shared_ptr<ecs::Component> &player,
                                     const std::shared_ptr<components::RulesComponent> &ruleComponent);
        static std::shared_ptr<is::ecs::Entity>
        createPresetSelectionPlayer4(std::shared_ptr<is::ecs::Entity> &e,
                                     const std::shared_ptr<ecs::Component> &player,
                                     const std::shared_ptr<components::RulesComponent> &ruleComponent);
        static std::shared_ptr<is::ecs::Entity> createPresetSelectionOptions(const is::ecs::ComponentManager &manager);


        static std::shared_ptr<is::ecs::Entity> createSettings();
        static std::shared_ptr<is::ecs::Entity> createControllersBase();
        static std::shared_ptr<is::ecs::Entity> createCharacter();
        static std::shared_ptr<is::ecs::Entity> createPresets();
        static std::shared_ptr<is::ecs::Entity> createJoystickCursor(int joystickId, std::shared_ptr<components::WindowComponent> &window);
        static std::shared_ptr<is::ecs::Entity> createControllersOptions(const is::ecs::ComponentManager &manager);

        static std::shared_ptr<is::ecs::Entity> createBomberman(const irr::core::vector3df &pos, is::components::CharacterComponent &character);
        static std::shared_ptr<is::ecs::Entity> createMultiplayerHub(std::shared_ptr<is::components::NetworkComponent> nc);
        static std::shared_ptr<is::ecs::Entity> createMultiplayerLobbyChoice(std::shared_ptr<is::components::NetworkComponent> nc);
        static std::shared_ptr<is::ecs::Entity> createMultiplayerLobby(std::shared_ptr<is::components::NetworkComponent> nc);
        static std::shared_ptr<is::ecs::Entity> createControllers();
        static std::shared_ptr<is::ecs::Entity> createRules();

        static std::shared_ptr<is::ecs::Entity> createTimer(is::components::RulesComponent &rules);

        private:
            static std::shared_ptr<is::ecs::Entity> createBomberman(const irr::core::vector3df &pos, is::components::CharacterComponent &character, const std::string &texture);
    };

}

#endif /* !GLOBALPREFABS_HPP_ */

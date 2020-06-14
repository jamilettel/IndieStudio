/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Entity
*/

#ifndef MAP_LOADER_HPP_
#define MAP_LOADER_HPP_

#include <vector>
#include <string>
#include <irrlicht.h>
#include "Components/Character.hpp"
#include "Components/Transform.hpp"
#include "ECS/ComponentManager.hpp"
#include "ECS/Entity.hpp"
#include "Components/PowerUp.hpp"
#include <fstream>
#include "Components/Bomberman.hpp"

namespace is {

    struct CharacterInfo {
        irr::core::vector3df position;
        is::components::CharacterComponent::Type type;
        int level;
        int preset;
        bool alive;
        int bombNumber;
        int speedUp;
        float speedMult;
        int bombRange;
        bool wallPass;
        size_t bombPosed;
        size_t bonusCollected;
        size_t kills;
        size_t time;
    };
    
    struct BonusInfo {
        irr::core::vector3df position;
        is::components::PowerUpComponent::PowerUpType type;
    };

    class MapLoader {
        public:
            MapLoader();
            ~MapLoader() = default;

            MapLoader(const MapLoader &) = default;
            MapLoader &operator=(const MapLoader &) = default;

            static void addBonusToSave(components::TransformComponent &tr, size_t bonusCount);
            static void addPlayerToSave(components::TransformComponent &tr, size_t playerCount);
            
            static int typeToInt(components::CharacterComponent::Type type);
            static int typeToInt(components::PowerUpComponent::PowerUpType type);
            static components::CharacterComponent::Type stringToType(const std::string &string);
            static components::PowerUpComponent::PowerUpType stringToTypeBonus(const std::string &string);
            
            static int layerToInt(ecs::Entity::Layer layer, int x, int y);
            static std::vector<std::vector<int>> loadMap(const std::string &file);
            static void saveMap(const std::string &file);
            
            static float timer;
            static int x;
            static int y;
            
            static bool icons[4];
            static int powerUpFrequency;
            static float maxTime;
            static size_t playerNumber;
            static size_t bonusNumber;
            static std::vector<CharacterInfo> charactersInfo;
            static std::vector<BonusInfo> bonusInfo;
            static std::shared_ptr<is::ecs::ComponentManager> componentManager;

            template<typename T>
            static T fileWord(std::ifstream &stream) {
                T toReturn;
                stream >> toReturn;
                return (toReturn);
            }
    };
}

#endif
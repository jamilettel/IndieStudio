/*
** EPITECH PROJECT, 2020
** bomberman
** File description:
** Map Loader
*/

#include "MapLoader.hpp"
#include <iostream>
#include "Components/AIController.hpp"
#include "Components/CharacterController.hpp"

using namespace is;
using namespace is::components;
using namespace is::ecs;

int MapLoader::x = 0;
int MapLoader::y = 0;

size_t MapLoader::playerNumber = 0;
size_t MapLoader::bonusNumber = 0;

std::vector<is::CharacterInfo> MapLoader::charactersInfo;
std::vector<is::BonusInfo> MapLoader::bonusInfo;
std::shared_ptr<is::ecs::ComponentManager> MapLoader::componentManager;

MapLoader::MapLoader()
{
}

std::vector<std::vector<int>> MapLoader::loadMap(const std::string &file)
{
    std::ifstream toLoad(file);
    std::vector<std::vector<int>> toReturn;

    MapLoader::y = fileWord<int>(toLoad);
    MapLoader::x = fileWord<int>(toLoad);

    for (int e = 0; e < y; e++) {
        toReturn.emplace_back(x);
        for (int z = 0; z < x; z++) {
            toReturn[e][z] = fileWord<int>(toLoad);
        }
    }

    playerNumber = fileWord<size_t>(toLoad);
    std::cout << playerNumber << std::endl;
    for (size_t i = 0; i < playerNumber; i++) {
        CharacterInfo tmp;
        tmp.type = stringToType(fileWord<std::string>(toLoad));
        tmp.position.X = fileWord<float>(toLoad);
        tmp.position.Z = fileWord<float>(toLoad);
        tmp.level = fileWord<int>(toLoad);
        tmp.preset = fileWord<int>(toLoad);
        tmp.bombNumber = fileWord<int>(toLoad);
        tmp.speedUp = fileWord<int>(toLoad);
        tmp.speedMult = fileWord<float>(toLoad);
        tmp.bombRange = fileWord<int>(toLoad);
        std::cout << "bombrange : " << tmp.bombRange << std::endl;
        tmp.wallPass = (fileWord<int>(toLoad) == 1) ? true : false;
        tmp.bombPosed = fileWord<int>(toLoad);
        tmp.bonusCollected = fileWord<int>(toLoad);
        tmp.kills = fileWord<int>(toLoad);
        tmp.position.Y = 0;
        std::cout << tmp.position.X << "   " <<  tmp.position.Z << std::endl;
        if (charactersInfo.size() <= i)
            charactersInfo.push_back(tmp);
        else
            charactersInfo[i] = tmp;
    }

    bonusNumber = fileWord<size_t>(toLoad);
    std::cout << bonusNumber << std::endl;
    for (size_t i = 0; i < bonusNumber; i++) {
        BonusInfo tmpBonus;
        tmpBonus.type = stringToTypeBonus(fileWord<std::string>(toLoad));
        tmpBonus.position.X = fileWord<float>(toLoad);
        tmpBonus.position.Z = fileWord<float>(toLoad);
        tmpBonus.position.Y = 0;
        if (bonusInfo.size() <= i)
            bonusInfo.push_back(tmpBonus);
        else
            bonusInfo[i] = tmpBonus;
    }

    return (toReturn);
}

void MapLoader::saveMap(const std::string &file)
{
    size_t playerCount = 0;
    size_t bonusCount = 0;
    std::vector<std::vector<int>> map(13, std::vector<int>(15, 0));
    std::vector<std::shared_ptr<Component>> &trComponents = 
        componentManager->getComponentsByType(typeid(TransformComponent).hash_code());

    std::cout << trComponents.size() << std::endl;
    for (std::shared_ptr<Component> &component: trComponents) {
        TransformComponent &tr = *static_cast<TransformComponent *>(component.get());
        if (tr.getEntity()->layer == Entity::Layer::PLAYER) {
            addPlayerToSave(tr, playerCount);
            playerCount++;
        } else if (tr.getEntity()->layer == Entity::Layer::POWERUP) {
            addBonusToSave(tr, bonusCount);
            bonusCount++;
        }
        if (tr.position.Y < 0)
            continue;
        int x = (tr.position.X) / 3 + (int)(15 / 2);
        int y = (tr.position.Z) / 3 + (int)(13 / 2);
        if (x > 12 || y > 14 || x < 0 || y < 0)
            continue;
        map[x -1][y + 1] = layerToInt(tr.getEntity()->layer, x , y);
    }

    std::ofstream toSave(file);

    toSave << 13 << " " << 15 << " " << std::endl;
    for (size_t i = 0; i < map.size(); i++) {
        for (size_t j = 0; j < map[i].size(); j++) {
            if (i == 0 || j == 0 || j == 15 - 1 || i == 13 -1)
                toSave << 3 << " ";
            else if (!(i % 2) && !(j % 2))
                toSave << 2 << " ";
            else
                toSave << map[i][j] << " ";
        }
        toSave << std::endl;
    }

    toSave << std::endl;
    toSave << playerCount << std::endl;


    for (size_t i = 0; i < playerCount; i++) {
        toSave << typeToInt(charactersInfo[i].type) << " ";
        toSave << charactersInfo[i].position.X << " ";
        toSave << charactersInfo[i].position.Z << " ";
        toSave << charactersInfo[i].level << " ";
        toSave << charactersInfo[i].preset << " ";
        toSave << charactersInfo[i].bombNumber << " ";
        toSave << charactersInfo[i].speedUp << " ";
        toSave << charactersInfo[i].speedMult << " ";
        toSave << charactersInfo[i].bombRange << " ";
        toSave << ((charactersInfo[i].wallPass) ? 1 : 0) << " ";
        toSave << charactersInfo[i].bombPosed << " ";
        toSave << charactersInfo[i].bonusCollected << " ";
        toSave << charactersInfo[i].kills << " ";
        toSave << std::endl;
    }

    toSave << std::endl;
    toSave << bonusCount << std::endl;
    
    for (size_t i = 0; i < bonusCount; i++) {
        toSave << typeToInt(bonusInfo[i].type) << " ";
        toSave << bonusInfo[i].position.X << " ";
        toSave << bonusInfo[i].position.Z << " ";
        toSave << std::endl;
    }

}

void MapLoader::addBonusToSave(TransformComponent &tr, size_t bonusCount)
{
    BonusInfo tmp;

    tmp.type = tr.getEntity()->getComponent<PowerUpComponent>().value()->type;
    tmp.position = tr.position;
    if (bonusInfo.size() <= bonusCount)
        bonusInfo.push_back(tmp);
    else
        bonusInfo[bonusCount] = tmp;
}

void MapLoader::addPlayerToSave(TransformComponent &tr, size_t playerCount)
{
    CharacterInfo tmp;
    CharacterComponent &ch = tr.getEntity()->getComponent<CharacterControllerComponent>().value()->getCharacterComponent();
    BombermanComponent *bm = tr.getEntity()->getComponent<BombermanComponent>()->get();
    tmp.position = tr.position;
    tmp.preset =
        ch.presetNumber;
    tmp.type = ch.characterType;
    tmp.level = (tmp.type == CharacterComponent::Type::AI) ? 
        tr.getEntity()->getComponent<AIControllerComponent>().value()->getLevel() : 0;
    tmp.bombNumber = bm->bombNumber ;
    tmp.speedUp = bm->speedCount;
    tmp.speedMult = bm->speedMult;
    tmp.bombRange = bm->bombRange;
    std::cout << "bombrange : " << tmp.bombRange << std::endl;
    tmp.wallPass = bm->wallPass;
    tmp.bombPosed = ch.getNbBombPosed();
    tmp.bonusCollected = ch.getNbBonusCollected();
    tmp.kills = ch.getNbCharactersKilled();
    if (charactersInfo.size() <= playerCount)
        charactersInfo.push_back(tmp);
    else
        charactersInfo[playerCount] = tmp;
}

int MapLoader::layerToInt(Entity::Layer layer, int x, int y)
{
    switch (layer) {
        case (Entity::Layer::DEFAULT):
            if (x == 0 || y == 0 || x == 12 || y == 14)
                return (3);
            return (2);
        case (Entity::Layer::BRKBL_BLK):
            return (1);
        default:
            return (0);
    }    
}

is::components::PowerUpComponent::PowerUpType MapLoader::stringToTypeBonus(const std::string &string)
{
    if (string == "0")
        return (is::components::PowerUpComponent::PowerUpType::BOMB_UP);
    else if (string == "1")
        return (is::components::PowerUpComponent::PowerUpType::FIRE_UP);
    else if (string == "2")
        return (is::components::PowerUpComponent::PowerUpType::SPEED_UP);
    else
        return (is::components::PowerUpComponent::PowerUpType::WALL_PASS);
}

int MapLoader::typeToInt(is::components::PowerUpComponent::PowerUpType type)
{
    switch (type) {
        case (PowerUpComponent::PowerUpType::BOMB_UP):
            return (0);
        case (PowerUpComponent::PowerUpType::FIRE_UP):
            return (1);
        case (PowerUpComponent::PowerUpType::SPEED_UP):
            return (2);
        default:
            return (3);
    }
}

is::components::CharacterComponent::Type MapLoader::stringToType(const std::string &string)
{
    if (string == "0")
        return (is::components::CharacterComponent::Type::AI);
    else if (string == "1")
        return (is::components::CharacterComponent::Type::JOYSTICK_PLAYER);
    else
        return (is::components::CharacterComponent::Type::KEYBOARD_PLAYER);
}

int MapLoader::typeToInt(is::components::CharacterComponent::Type type)
{
    switch (type) {
        case (CharacterComponent::Type::AI):
            return (0);
        case (CharacterComponent::Type::JOYSTICK_PLAYER):
            return (1);
        default:
            return (2);
    }
}
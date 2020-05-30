/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** NetworkSystem
*/

#include "Systems/Network.hpp"
#include <algorithm>

using namespace irr;
using namespace std;

void is::systems::NetworkSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::NetworkComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("MultiplayerScene::initEntities", "Could not get NetworkComponent pointer");
        if (ptr->isOn)
            continue;
        try {
            ptr->startMultiplayer();
        } catch(const std::exception &e) {
            std::cout << e.what() << std::endl;
            //is::Game::setActualScene(is::ecs::SCENE_MAIN_MENU);
            //ptr->getEntity()->setDelete(true);
        }
    }
}

void is::systems::NetworkSystem::start()
{

}

void is::systems::NetworkSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::NetworkComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("NetworkSystem", "Could not get NetworkComponent pointer");
        if (!ptr->isOn)
            continue;
        if (is::Game::getCurrentScene() == is::ecs::Scenes::SCENE_MULTIPLAYER_GAME)
            refreshGameState(ptr);
        selectHandling(ptr);
    }
}

void is::systems::NetworkSystem::refreshGameState(std::shared_ptr<is::components::NetworkComponent> ptr)
{
    auto characters = _componentManager->getComponentsByType(typeid(is::components::CharacterControllerComponent).hash_code());
    auto ptr_char = std::dynamic_pointer_cast<is::components::CharacterControllerComponent>(characters[ptr->playerIdx]);
    if (!ptr_char)
        throw is::exceptions::Exception("NetworkSystem", "Could not get CharacterControllerComponent pointer");
    auto tr = ptr_char->getEntity()->getComponent<is::components::TransformComponent>()->get();
    if (!tr)
        throw is::exceptions::Exception("CharacterControllerSystem", "Could not found bomberman");
    
    irr::core::vector3df playerPos = tr->position;
    // TODO: put time to PS event every X time
    ptr->writeQueue.push("evt ps " + std::to_string(ptr->lobby) +
        " " + std::to_string(ptr->playerIdx) + " " +
        std::to_string(playerPos.X) + " " + std::to_string(playerPos.Z) + " " +
        std::to_string(tr->rotation.Y) + " \n");
    if (ptr_char->dropBombFrame) {
        ptr->writeQueue.push("evt db " + std::to_string(ptr->lobby) +
        " " + std::to_string(ptr->playerIdx) + " \n");
    }
}

void is::systems::NetworkSystem::selectHandling(std::shared_ptr<is::components::NetworkComponent> ptr) // TODO: Tristan debug ici stp mec.
{
    if (select(ptr->serverSock + 1, &ptr->rfds, &ptr->wfds, &ptr->efds, &ptr->timeout) == -1)
        throw is::exceptions::Exception("NetworkSystem", "Select exception");        
    char buff[READ_SIZE] = {0};
    if (recv(ptr->serverSock, buff, READ_SIZE, MSG_DONTWAIT) >= 0) { // WINDOW CONNAIT PAS DONTWAIT
        //std::cout << "<- " << buff << std::endl;
        std::vector<std::string> cmd;
        split(std::string(buff), cmd, ' ');
        if (cmd[0] == "res") {
            if (cmd[1] == "cl" || cmd[1] == "jl") {
                ptr->lobby = atoi(cmd[2].c_str());
                is::Game::setActualScene(is::ecs::Scenes::SCENE_MULTIPLAYER_LOBBY);
            } else if (cmd[1] == "sg") {
                ptr->playerIdx = atoi(cmd[2].c_str());
                if (ptr->playerIdx < 0 || ptr->playerIdx > 3)
                    throw is::exceptions::Exception("NetworkSystem", "init multiplayer game exception");        
                for (int i = 0; i < 4; i++) {
                    auto characters = _componentManager->getComponentsByType(typeid(is::components::CharacterComponent).hash_code());
                    auto ptr_char = std::dynamic_pointer_cast<is::components::CharacterComponent>(characters[i]);
                    if (!ptr_char)
                        throw is::exceptions::Exception("NetworkSystem", "Could not get CharacterComponent pointer");
                    if (i == ptr->playerIdx) {
                        ptr_char->characterType = is::components::CharacterComponent::Type::KEYBOARD_PLAYER;
                        ptr_char->presetNumber = 1;
                    }
                    else {
                        ptr_char->characterType = is::components::CharacterComponent::Type::MULTIPLAYER_PLAYER;
                        ptr_char->multiplayerId = i;
                    }
                }
                is::Game::setActualScene(is::ecs::Scenes::SCENE_MULTIPLAYER_GAME);
            }
        } else if (cmd[0] == "evt") {
            if (cmd[1] == "ps") {            
                int idx = atoi(cmd[3].c_str());
                float posX = atof(cmd[4].c_str());
                float posY = atof(cmd[5].c_str());
                float rotY = atof(cmd[6].c_str());
            
                ptr->playerStates[idx].position = irr::core::vector2df(posX, posY);
                ptr->playerStates[idx].rotationY = rotY;
            }
            if (cmd[1] == "db") {            
                int idx = atoi(cmd[3].c_str());

                std::cout << "DB" << std::endl;
                ptr->playerStates[idx].dropBomb = true;
            }
            if (cmd[1] == "pu") {            
                int idx = atoi(cmd[3].c_str());
                int pu = atoi(cmd[4].c_str());
                int posX = atoi(cmd[5].c_str());
                int posY = atoi(cmd[6].c_str());

                std::cout << "PU" << std::endl;
                ptr->playerStates[idx].powerUpSpawn = pu;
                ptr->playerStates[idx].positionPowerUp.X = posX;
                ptr->playerStates[idx].positionPowerUp.Y = posY;
            }
        }
    }
    //if (recv(ptr->serverSockUdp, buff, READ_SIZE, MSG_DONTWAIT) >= 0) { // WINDOW CONNAIT PAS DONTWAIT
    //    std::cout << buff << std::endl;
    //}
    if (FD_ISSET(ptr->serverSock, &ptr->wfds)) {
        if (ptr->writeQueue.size() > 0) {
            std::string tmp = ptr->writeQueue.front();
            //std::cout << "-> " << tmp << std::endl;
            write(ptr->serverSock, tmp.c_str(), tmp.size());
            ptr->writeQueue.pop();
        }
    }
    //if (ptr->writeQueueUdp.size() > 0) {
    //    std::string tmp = ptr->writeQueueUdp.front();
    //    sendto(ptr->serverSockUdp, (const char*)tmp.c_str(), tmp.size(), 0, (const struct sockaddr*)&ptr->addr, sizeof(ptr->addr)); 
    //    ptr->writeQueueUdp.pop();
    //}
    if (FD_ISSET(ptr->serverSock, &ptr->efds)) {
        close(ptr->serverSock);
        close(ptr->serverSockUdp);
        ptr->isOn = false;
    }
    //if (FD_ISSET(ptr->serverSockUdp, &ptr->efds)) {
    //    close(ptr->serverSockUdp);
    //    close(ptr->serverSock);
    //    ptr->isOn = false;
    //}
}

void is::systems::NetworkSystem::stop()
{

}

void is::systems::NetworkSystem::onTearDown()
{

}

size_t is::systems::NetworkSystem::split(const std::string &str, std::vector<std::string> &strs, char ch)
{
    size_t pos = str.find(ch);
    size_t initialPos = 0;

    strs.clear();
    while(pos != std::string::npos) {
        strs.push_back( str.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;
        pos = str.find(ch, initialPos);
    }
    strs.push_back(str.substr(initialPos, min(pos, str.size()) - initialPos + 1 ));
    return (strs.size());
}

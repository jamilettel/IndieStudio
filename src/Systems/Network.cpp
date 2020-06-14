/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** NetworkSystem
*/

#include "Systems/Network.hpp"
#include <algorithm>

#ifndef MSG_DONTWAIT
#define MSG_DONTWAIT 0x40
#endif

using namespace irr;
using namespace std;

void is::systems::NetworkSystem::awake()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code())) {
        const auto &ptr = static_cast<is::components::NetworkComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("MultiplayerScene::initEntities", "Could not get NetworkComponent pointer");
        if (ptr->isOn)
            continue;
        try {
            ptr->startMultiplayer();
        } catch(const std::exception &e) {
            const auto &alertComponent = static_cast<AlertComponent*>(_componentManager->getComponentsByType(typeid(AlertComponent).hash_code())[0].get());
            alertComponent->addAlert("Can't connect to server", []() {
                is::Game::setActualScene(is::ecs::SCENE_MAIN_MENU);
            });
            ptr->isLock = true;
        }
    }
}

void is::systems::NetworkSystem::start()
{
    std::vector<std::shared_ptr<is::ecs::Component>> &time =
        _componentManager->getComponentsByType(typeid(is::components::TimeComponent).hash_code());

    if (!time.size())
        throw is::exceptions::Exception("NetworkSystem", "No time component in scene");
    _time.emplace(*static_cast<is::components::TimeComponent *>(time[0].get()));
}

void is::systems::NetworkSystem::update()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code())) {
        const auto &ptr = std::static_pointer_cast<is::components::NetworkComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("NetworkSystem", "Could not get NetworkComponent pointer");
        if (!ptr->isOn)
            continue;
        if (is::Game::getCurrentScene() == is::ecs::Scenes::SCENE_MULTIPLAYER_GAME)
            refreshGameState(ptr);
        selectHandling(ptr);
    }
}

void is::systems::NetworkSystem::refreshGameState(const std::shared_ptr<is::components::NetworkComponent> &ptr)
{
    const auto &charactersCo = _componentManager->getComponentsByType(typeid(is::components::CharacterComponent).hash_code());
    const auto &characters = _componentManager->getComponentsByType(typeid(is::components::CharacterControllerComponent).hash_code());
    const auto &ptr_char = static_cast<is::components::CharacterControllerComponent *>(characters[ptr->playerIdx].get());

    if (!ptr_char)
        throw is::exceptions::Exception("NetworkSystem", "Could not get CharacterControllerComponent pointer");
    const auto &tr = ptr_char->getEntity()->getComponent<is::components::TransformComponent>()->get();
    if (!tr)
        throw is::exceptions::Exception("NetworkSystem", "Could not found transform");

    irr::core::vector3df playerPos = tr->position;
    ptr->timeBeforeSharePos += _time->get().getCurrentIntervalSeconds();
    ptr->timeBeforeSharePosAi += _time->get().getCurrentIntervalSeconds();
    if (ptr->playerIdx == 0 && ptr->timeBeforeSharePosAi >= 0.05f) {
        for (size_t i = 0; i < characters.size(); i++) {
            auto &ch = *static_cast<CharacterComponent *>(charactersCo[i].get());
            if (ch.characterType == is::components::CharacterComponent::AI) {
                const auto &trAi = characters[i]->getEntity()->getComponent<is::components::TransformComponent>()->get();
                if (!trAi)
                    throw is::exceptions::Exception("NetworkSystem", "Could not found transform");
                irr::core::vector3df playerPosAi = trAi->position;
                ptr->writeQueue.push("evt ps " + std::to_string(ptr->lobby) +
                    " " + std::to_string(i) + " " +
                    std::to_string(playerPosAi.X) + " " + std::to_string(playerPosAi.Z) + " " +
                    std::to_string(trAi->rotation.Y) + " \n");
            }
        }
        ptr->timeBeforeSharePosAi = 0;
    }
    if (ptr_char->lastPos != playerPos && ptr->timeBeforeSharePos >= 0.05f) {    
        ptr->writeQueue.push("evt ps " + std::to_string(ptr->lobby) +
            " " + std::to_string(ptr->playerIdx) + " " +
            std::to_string(playerPos.X) + " " + std::to_string(playerPos.Z) + " " +
            std::to_string(tr->rotation.Y) + " \n");
        ptr->timeBeforeSharePos = 0;
    }
    
    for (size_t i = 0; i < characters.size(); i++) {
        if (static_cast<is::components::CharacterControllerComponent *>(characters[i].get())->dropBombFrame) { 
            ptr->writeQueue.push("evt db " + std::to_string(ptr->lobby) +
            " " + std::to_string(i) + " \n");
        }
    }
}

void is::systems::NetworkSystem::selectHandling(const std::shared_ptr<is::components::NetworkComponent> &ptr) // TODO: Tristan debug ici stp mec.
{
    if (select(ptr->serverSock + 1, &ptr->rfds, &ptr->wfds, &ptr->efds, &ptr->timeout) == -1)
        throw is::exceptions::Exception("NetworkSystem", "Select exception");        
    char buff[READ_SIZE] = {0};
    #ifdef _WIN32
    u_long mode = 1;
    ioctlsocket(ptr->serverSock, FIONBIO, &mode);
    if (recv(ptr->serverSock, buff, READ_SIZE, 0) >= 0) {
    #else
    if (recv(ptr->serverSock, buff, READ_SIZE, MSG_DONTWAIT) >= 0) {
    #endif
        std::vector<std::string> cmd;
        split(std::string(buff), cmd, ' ');
        int remove = 0;
        while (cmd.size() > 1) {
            if (cmd[0] == "err") {
                if (cmd [1] == "lnf") {
                    const auto &alertComponent = static_cast<AlertComponent*>(_componentManager->getComponentsByType(typeid(AlertComponent).hash_code())[0].get());
                    alertComponent->addAlert("Lobby not found", []() {
                        is::Game::setActualScene(is::ecs::SCENE_MULTIPLAYER_HUB);
                    });
                    remove = 2;
                }
            }
            else if (cmd[0] == "res") {
                if (cmd[1] == "cl" || cmd[1] == "jl") {
                    ptr->lobby = atoi(cmd[2].c_str());
                    is::Game::setActualScene(is::ecs::Scenes::SCENE_MULTIPLAYER_LOBBY);
                    remove = 3;
                } else if (cmd[1] == "sg") {
                    int nb = atoi(cmd[3].c_str());
                    int nbAi = atoi(cmd[4].c_str());
                    float time = atof(cmd[5].c_str());

                    ptr->playerIdx = atoi(cmd[2].c_str());

                    static_cast<RulesComponent *>(_componentManager->getComponentsByType(typeid(RulesComponent).hash_code())[0].get())->setNumberOfPlayers(nb);
                    static_cast<RulesComponent *>(_componentManager->getComponentsByType(typeid(RulesComponent).hash_code())[0].get())->setMaxTime(time);
                    
                    if (ptr->playerIdx < 0 || ptr->playerIdx > 3)
                        throw is::exceptions::Exception("NetworkSystem", "init multiplayer game exception");        
                    for (int i = 0; i < 4; i++) {
                        const auto &characters = _componentManager->getComponentsByType(typeid(is::components::CharacterComponent).hash_code());
                        const auto &ptr_char = static_cast<is::components::CharacterComponent*>(characters[i].get());
                        if (!ptr_char)
                            throw is::exceptions::Exception("NetworkSystem", "Could not get CharacterComponent pointer");
                        if (i == ptr->playerIdx) {
                            ptr_char->characterType = is::components::CharacterComponent::Type::KEYBOARD_PLAYER;
                            ptr_char->presetNumber = 1;
                        } else {
                            if (ptr->playerIdx == 0 && i >= nb - nbAi) {
                                ptr_char->characterType = is::components::CharacterComponent::Type::AI;
                                
                            } else {
                                ptr_char->characterType = is::components::CharacterComponent::Type::MULTIPLAYER_PLAYER;
                                ptr_char->multiplayerId = i;
                            }
                        }
                    }
                    is::Game::setActualScene(is::ecs::Scenes::SCENE_MULTIPLAYER_GAME);
                    remove = 6;
                }
            } else if (cmd[0] == "evt") {
                if (cmd[1] == "ps") {            
                    int idx = atoi(cmd[3].c_str());
                    float posX = atof(cmd[4].c_str());
                    float posY = atof(cmd[5].c_str());
                    float rotY = atof(cmd[6].c_str());

                    ptr->playerStates[idx].position = irr::core::vector2df(posX, posY);
                    ptr->playerStates[idx].rotationY = rotY;
                    remove = 7;
                }
                if (cmd[1] == "db") {
                    int idx = atoi(cmd[3].c_str());
                
                    ptr->playerStates[idx].dropBomb = true;
                    remove = 4;
                }
                if (cmd[1] == "pu") {
                    int idx = atoi(cmd[3].c_str());
                    int pu = atoi(cmd[4].c_str());
                    int posX = atoi(cmd[5].c_str());
                    int posY = atoi(cmd[6].c_str());

                    ptr->playerStates[idx].powerUpSpawn = pu;
                    ptr->playerStates[idx].positionPowerUp.X = posX;
                    ptr->playerStates[idx].positionPowerUp.Y = posY;
                    remove = 7;
                }
                if (cmd[1] == "gpu") {
                    int idx = atoi(cmd[3].c_str());
                    int pu = atoi(cmd[4].c_str());

                    ptr->playerStates[idx].powerUpTake = pu;
                    remove = 5;
                }
                if (cmd[1] == "bb") {  
                    float posX = atoi(cmd[3].c_str());
                    float posY = atoi(cmd[4].c_str());
        
                    std::vector<std::shared_ptr<is::ecs::Component>> &window =
                    _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code());
                    if (!window.size())
                        throw is::exceptions::Exception("Network", "No window component in scene");
                    const auto &ptr_window = std::static_pointer_cast<is::components::WindowComponent>(window[0]);
                    std::shared_ptr<is::ecs::Entity> e = initRuntimeEntity(prefabs::GlobalPrefabs::createBreakableBlock(irr::core::vector3df(posX, 0, posY)));
                    const auto &modelRenderer = static_cast<is::components::ModelRendererComponent*>(e->getComponent<is::components::ModelRendererComponent>()->get());
                    modelRenderer->initModelRenderer(std::move(ptr_window));
                    remove = 5;
                }
            }
            cmd.erase(cmd.begin(), cmd.begin() + remove);
        }
    }
    if (FD_ISSET(ptr->serverSock, &ptr->wfds)) {
        if (ptr->writeQueue.size() > 0) {
            std::string tmp = ptr->writeQueue.front();
#ifdef _WIN32
            send(ptr->serverSock, tmp.c_str(), tmp.size(), 0);
#else
            write(ptr->serverSock, tmp.c_str(), tmp.size());
#endif
            ptr->writeQueue.pop();
        }
    }
    if (FD_ISSET(ptr->serverSock, &ptr->efds)) {
#ifdef _WIN32
        _close(ptr->serverSock);
        _close(ptr->serverSockUdp);
#else
        close(ptr->serverSock);
        close(ptr->serverSockUdp);
#endif
        ptr->isOn = false;
    }
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

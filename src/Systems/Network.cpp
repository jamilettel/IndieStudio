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
        if (is::Game::getCurrentScene() == is::ecs::Scenes::SCENE_MULTIPLAYER_GAME) {
            auto characters = _componentManager->getComponentsByType(typeid(is::components::CharacterControllerComponent).hash_code());
            auto ptr_char = std::dynamic_pointer_cast<is::components::CharacterControllerComponent>(characters[ptr->playerIdx]);
            if (!ptr_char)
                throw is::exceptions::Exception("NetworkSystem", "Could not get CharacterControllerComponent pointer");
            auto e = ptr_char->getEntity()->getComponent<is::components::TransformComponent>()->get();
            irr::core::vector3df a = e->position;
            ptr->writeQueue.push("s" + std::to_string(ptr->playerIdx) + " " + std::to_string(a.X) + " " + std::to_string(a.Z) + " \n");
        }
        selectHandling(ptr);
    }
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

void is::systems::NetworkSystem::selectHandling(std::shared_ptr<is::components::NetworkComponent> ptr) // TODO: Tristan debug ici stp mec.
{

    // if (select(ptr->serverSock + 1, &ptr->rfds, &ptr->wfds, &ptr->efds, &ptr->timeout) == -1)
    //     throw is::exceptions::Exception("NetworkSystem", "Select exception");        
    // char buff[1024] = {0};
    // if (recv(ptr->serverSock, buff, 1024, MSG_DONTWAIT) >= 0) { // WINDOW CONNAIT PAS DONTWAIT
    //     if (std::string(buff) == "lobby created\n" || std::string(buff) == "lobby joined\n") {
    //         is::Game::setActualScene(is::ecs::Scenes::SCENE_MULTIPLAYER_LOBBY);
    //     } else if (strlen(buff) > 2 && buff[0] == 'p' && isdigit(buff[1])) {
    //         ptr->playerIdx = atoi(&buff[1]);
    //         if (ptr->playerIdx < 0 || ptr->playerIdx > 3)
    //             throw is::exceptions::Exception("NetworkSystem", "init multiplayer game exception");        
    //         for (int i = 0; i < 4; i++) {
    //             auto characters = _componentManager->getComponentsByType(typeid(is::components::CharacterComponent).hash_code());
    //             auto ptr_char = std::dynamic_pointer_cast<is::components::CharacterComponent>(characters[i]);
    //             if (!ptr_char)
    //                 throw is::exceptions::Exception("NetworkSystem", "Could not get CharacterComponent pointer");
    //             if (i == ptr->playerIdx) {
    //                 ptr_char->characterType = is::components::CharacterComponent::Type::KEYBOARD_PLAYER;
    //                 ptr_char->presetNumber = 1;
    //             }
    //             else {
    //                 ptr_char->characterType = is::components::CharacterComponent::Type::MULTIPLAYER_PLAYER;
    //                 ptr_char->multiplayerId = i;
    //             }
    //         }
    //         is::Game::setActualScene(is::ecs::Scenes::SCENE_MULTIPLAYER_GAME);
    //     } else if (strlen(buff) > 2 && buff[0] == 's' && isdigit(buff[1])) {            
    //         int idx = atoi(&buff[1]);
    //         std::vector<std::string> v;
    //         split(std::string(buff), v, ' ');
    //         float x = atof(v[1].c_str());
    //         float y = atof(v[2].c_str());
    //         auto characters = _componentManager->getComponentsByType(typeid(is::components::CharacterControllerComponent).hash_code());
    //         auto ptr_char = std::dynamic_pointer_cast<is::components::CharacterControllerComponent>(characters[idx]);
    //         if (!ptr_char)
    //             throw is::exceptions::Exception("NetworkSystem", "Could not get CharacterControllerComponent pointer");
    //         auto e = ptr_char->getEntity()->getComponent<is::components::TransformComponent>()->get();
    //         ptr->playerPositions[idx] = irr::core::vector2df(x, y);
    //     }
    // }
    // if (FD_ISSET(ptr->serverSock, &ptr->wfds)) {
    //     if (ptr->writeQueue.size() > 0) {
    //         std::string tmp = ptr->writeQueue.front();
    //         write(ptr->serverSock, tmp.c_str(), tmp.size());
    //         ptr->writeQueue.pop();
    //     }
    // }
    // if (FD_ISSET(ptr->serverSock, &ptr->efds)) {
    //     close(ptr->serverSock);
    //     ptr->isOn = false;
    // }
}

void is::systems::NetworkSystem::stop()
{

}

void is::systems::NetworkSystem::onTearDown()
{

}


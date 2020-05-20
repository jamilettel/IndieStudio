/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** NetworkSystem
*/

#include "Systems/Network.hpp"

using namespace irr;

void is::systems::NetworkSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::NetworkComponent).hash_code())) {
        auto ptr = std::dynamic_pointer_cast<is::components::NetworkComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("MultiplayerScene::initEntities", "Could not get NetworkComponent pointer");
        try {
            ptr->startMultiplayer();
        } catch(const std::exception &e) {
            std::cout << e.what() << std::endl;
            is::Game::setActualScene(is::ecs::SCENE_MAIN_MENU);
            ptr->getEntity()->setDelete(true);
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
        if (select(ptr->serverSock + 1, &ptr->rfds, &ptr->wfds, &ptr->efds, &ptr->timeout) == -1)
            throw is::exceptions::Exception("NetworkSystem", "Select exception");
        if (FD_ISSET(ptr->serverSock, &ptr->rfds)) {
            char buff[1024] = {0};
            if (read(ptr->serverSock, buff, 1024) < 0)
                throw is::exceptions::Exception("NetworkSystem", "read exception");
            ptr->readQueue.push(std::string(buff));
        }
        if (FD_ISSET(ptr->serverSock, &ptr->rfds)) {
            std::string tmp = ptr->writeQueue.front();
            write(ptr->serverSock, tmp.c_str(), tmp.size());
            ptr->writeQueue.pop();
        }
        if (FD_ISSET(ptr->serverSock, &ptr->efds)) {
            close(ptr->serverSock);
            ptr->isOn = false;
        }
        
    }
}

void is::systems::NetworkSystem::stop()
{

}

void is::systems::NetworkSystem::onTearDown()
{

}


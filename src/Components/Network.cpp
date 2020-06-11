/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Network
*/

#include "Components/Network.hpp"
#include <iostream>

is::components::NetworkComponent::NetworkComponent(std::shared_ptr<is::ecs::Entity> &e) :
Component(e)
{
    isOn = false;
    isLock = false;
    timeout.tv_sec = 0;
    timeout.tv_usec = 10000;
}

void is::components::NetworkComponent::deleteComponent()
{
    
}

void is::components::NetworkComponent::startMultiplayer()
{
    int n = 1;

    if (isLock) {
        isOn = false;
        return;
    }

    // init player states
    playerStates.push_back({{-5 * 3, 6 * 3}, {0, 0}, 0, false, 0, 0});
    playerStates.push_back({{5 * 3, -6 * 3}, {0, 0}, 0, false, 0, 0});
    playerStates.push_back({{-5 * 3, -6 * 3}, {0, 0}, 0, false, 0, 0});
    playerStates.push_back({{5 * 3, 6 * 3}, {0, 0}, 0, false, 0, 0});
    timeBeforeSharePos = 0;
    timeBeforeSharePosAi = 0;
    
    // connect network to server
    if ((serverSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw is::exceptions::Exception("NetworkComponent", "socket TCP exception");
    if ((serverSockUdp = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        throw is::exceptions::Exception("NetworkComponent", "socket UDP exception");
    if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, (char *) &n, sizeof(n)) == -1)
        throw is::exceptions::Exception("NetworkComponent", "setsockopt exception");
    addr.sin_addr.s_addr = inet_addr("51.77.211.62");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    if (connect(serverSock, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        throw is::exceptions::Exception("NetworkComponent", "connect exception");
    
    // sets fds for select
    FD_ZERO(&rfds);
    FD_ZERO(&wfds);
    FD_ZERO(&efds);
    FD_SET(serverSock, &rfds);
    FD_SET(serverSock, &wfds);
    FD_SET(serverSock, &efds);
    FD_SET(serverSockUdp, &rfds);
    FD_SET(serverSockUdp, &wfds);
    FD_SET(serverSockUdp, &efds);
    isOn = true;
}

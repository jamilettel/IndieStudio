/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Network
*/

#ifndef Network_HPP_
#define Network_HPP_

#include <irrlicht.h>
#include <string>
#include <queue>

#include "ECS/Component.hpp"
#include "Exception.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

    #include <winsock2.h> 
    #include <io.h>
    #include <Ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")

#else

    #include <sys/select.h>
    #include <sys/socket.h>
    #include <sys/types.h>
    #include <netinet/ip.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>

#endif


namespace is::components {

    class NetworkComponent : public is::ecs::Component {
        public:
            explicit NetworkComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~NetworkComponent() override = default;

            NetworkComponent(const NetworkComponent &) = delete;
            NetworkComponent &operator=(const NetworkComponent &) = delete;

            void deleteComponent() override;
            void startMultiplayer();

            struct timeval timeout;
            fd_set rfds;
            fd_set wfds;
            fd_set efds;
            int serverSock;
            bool isOn;
            std::queue<std::string> writeQueue;
            std::queue<std::string> readQueue;
    };

}

#endif /* !Network_HPP_ */

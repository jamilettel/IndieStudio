/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Camera
*/

#ifndef Camera_HPP_
#define Camera_HPP_

#include <irrlicht.h>

#include <string>

#include "ECS/Component.hpp"

namespace is::components {

    class CameraComponent : public is::ecs::Component {
        public:
            explicit CameraComponent(std::shared_ptr<is::ecs::Entity> &e,
                            const std::string &cameraName = "MainCamera",
                            const std::string &windowName = "MainWindow",
                            const irr::core::vector3df& pos = irr::core::vector3df(0),
                            const irr::core::vector3df& rot = irr::core::vector3df(0));
            ~CameraComponent() override = default;

            CameraComponent(const CameraComponent &) = delete;
            CameraComponent &operator=(const CameraComponent &) = delete;

            void deleteComponent() override;

            irr::core::vector3df position;
            irr::core::vector3df rotation;

            std::string cameraName;
            std::string windowName;
    };

}

#endif /* !Camera_HPP_ */

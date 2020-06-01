/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef PARTICULECOMPONENT_HPP_
#define PARTICULECOMPONENT_HPP_

#include <irrlicht.h>

#include "ECS/Component.hpp"
#include "Components/Window.hpp"
#include "Exception.hpp"

typedef void (*particuleFunction)(irr::scene::IParticleSystemSceneNode *,
        const std::shared_ptr<is::components::WindowComponent> &ptr_window);

namespace is::components {

    enum PARTICULE {WICK, FIRE};

    class ParticuleComponent: public is::ecs::Component {

        public:
            ParticuleComponent(std::shared_ptr<is::ecs::Entity> &e, std::string wn, const irr::core::vector3df& position, PARTICULE particule);
            ~ParticuleComponent() override = default;

            ParticuleComponent(const ParticuleComponent &) = delete;
            ParticuleComponent &operator=(const ParticuleComponent &) = delete;

            void init(const std::shared_ptr<is::components::WindowComponent>& ptr_window);
            void deleteComponent() override;
            std::string windowName;
        private:
            irr::core::vector3df _position;
            irr::scene::IParticleSystemSceneNode *element{};
            PARTICULE _particule;
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

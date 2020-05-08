/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GlobalPrefabs
*/

#ifndef GLOBALPREFABS_HPP_
#define GLOBALPREFABS_HPP_

#include <memory>

#include "ECS/Entity.hpp"

#include "Components/Window.hpp"
#include "Components/Camera.hpp"
#include "Components/Transform.hpp"
#include "Components/ModelRenderer.hpp"
#include "Components/CharacterController.hpp"
#include "Components/Light.hpp"
#include "Components/Audio.hpp"
#include "Components/Collider.hpp"
#include "Components/Movement.hpp"
#include "Components/Gravity.hpp"
#include "Components/Bomb.hpp"
#include "Components/Fire.hpp"
#include "Components/Time.hpp"
#include "Components/ColliderTrigger.hpp"

namespace is::prefabs {

    class GlobalPrefabs {
    public:
        static std::shared_ptr<is::ecs::Entity> createGlobalPrefab();
        static std::shared_ptr<is::ecs::Entity> createWallBlock(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createBomb(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createFire(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createBreakableBlock(irr::core::vector3df position);
        static std::shared_ptr<is::ecs::Entity> createPlayer();
    };

}

#endif /* !GLOBALPREFABS_HPP_ */

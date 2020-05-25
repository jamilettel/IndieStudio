/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** RuleSettingsPrefabs
*/

#ifndef RULESETTINGSPREFABS_HPP_
#define RULESETTINGSPREFABS_HPP_

#include "ECS/Entity.hpp"

#include "Components/Texture.hpp"

#include <irrlicht.h>

#include <memory>

namespace is::prefabs
{
    class RuleSettingsPrefabs {
        public:
            static std::shared_ptr<is::ecs::Entity> createBackground();

        private:
    };
}


#endif /* !RULESETTINGSPREFABS_HPP_ */

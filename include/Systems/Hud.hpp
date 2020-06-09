/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Hud
*/

#ifndef HUD_HPP_
#define HUD_HPP_

#include "ECS/ASystem.hpp"

#include "Components/Hud.hpp"

namespace is::systems
{
    class HudSystem : public is::ecs::ASystem {
        public:
            HudSystem() = default;
            ~HudSystem() override = default;

            HudSystem(const HudSystem &) = default;
            HudSystem &operator=(const HudSystem &) = default;

            void awake() override;
            void start() override;
            void update() override;
            void stop() override;
            void onTearDown() override;
    };
}


#endif /* !HUD_HPP_ */

/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Hud
*/

#ifndef HUDCOMPONENT_HPP_
#define HUDCOMPONENT_HPP_

#include "ECS/Component.hpp"

#include "Components/Text.hpp"
#include "Components/Bomberman.hpp"

namespace is::components
{
    class HudComponent : public is::ecs::Component {
        public:
            HudComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                BombermanComponent &bm,
                TextComponent &bombNb,
                TextComponent &range,
                TextComponent &speed,
                TextComponent &pass
            );
            ~HudComponent() override = default;

            HudComponent(const HudComponent &) = delete;
            HudComponent &operator=(const HudComponent &) = delete;

            void deleteComponent() override;

            void update();

        private:
            BombermanComponent &_bm;
            TextComponent &_bombNb;
            TextComponent &_range;
            TextComponent &_speed;
            TextComponent &_pass;
    };
}


#endif /* !HUD_HPP_ */

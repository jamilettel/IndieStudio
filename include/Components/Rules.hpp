/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Rules
*/

#ifndef RULESCOMPONENT_HPP_
#define RULESCOMPONENT_HPP_

#include "ECS/Component.hpp"

#include <vector>
#include <map>
#include <string>

namespace is::components
{
    class RulesComponent : public is::ecs::Component {
        public:
            enum Icon
            {
                ACCELERATOR,
                EXPLOSION,
                BOMB,
                WALL_PASS
            };

        public:
            RulesComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~RulesComponent() = default;

            void deleteComponent() override;

            bool useIcon(Icon icon);
            void setIconUse(Icon icon, bool use) noexcept;
            void setNumberOfPlayers(int nb) noexcept;
            void setFpsMode(bool mode) noexcept;
            void setMaxTime(float time) noexcept;

            int getNumberOfPlayers() const noexcept;
            float getMaxTime() const noexcept;
            bool isFpsMode() const noexcept;

            bool noIconUsed() const noexcept;
            void setAllICons(bool used) noexcept;

            std::string getTimeString() const;


        private:
            int _numberOfPlayers = 4;
            std::map<Icon, bool> _icons;
            float _maxTime = 180; // in seconds
            bool _fpsMode = false;
    };
}


#endif /* !RULES_HPP_ */

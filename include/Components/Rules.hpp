/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Rules
*/

#ifndef RULESCOMPONENT_HPP_
#define RULESCOMPONENT_HPP_

#include <vector>
#include <map>
#include <string>

#include "ECS/Component.hpp"

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
            explicit RulesComponent(std::shared_ptr<is::ecs::Entity> &e);
            ~RulesComponent() override = default;

            void deleteComponent() override;

            bool useIcon(Icon icon);
            void setIconUse(Icon icon, bool use) noexcept;
            void setNumberOfPlayers(int nb) noexcept;
            void setFpsMode(bool mode) noexcept;
            void setMaxTime(float time) noexcept;

            [[nodiscard]] int getNumberOfPlayers() const noexcept;
            [[nodiscard]] float getMaxTime() const noexcept;
            [[nodiscard]] bool isFpsMode() const noexcept;

            [[nodiscard]] bool noIconUsed() const noexcept;
            void setAllICons(bool used) noexcept;

            [[nodiscard]] std::string getTimeString() const;

            [[nodiscard]] const std::vector<int> &getAiLevels() const;
            void setAiLevel(int ai, int level);

            [[nodiscard]] int getSeed() const noexcept;
            void incSeed() noexcept;
            void decSeed() noexcept;

            int getPowerupFrequency() const noexcept;
            void decPowerupFrequency() noexcept;
            void incPowerupFrequency() noexcept;

        private:
            int _numberOfPlayers = 4;
            std::map<Icon, bool> _icons;
            float _maxTime = 180; // in seconds
            bool _fpsMode = false;
            std::vector<int> _aiLevels;
            int _seed = 1;
            int _powerupFrequency = 7;
    };
}


#endif /* !RULES_HPP_ */

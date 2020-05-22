/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Stats
*/

#ifndef STATSCOMPONENT_HPP_
#define STATSCOMPONENT_HPP_

#include "ECS/Component.hpp"
#include "Components/Text.hpp"

#include <vector>

using namespace is::ecs;

namespace is::components
{
    class StatsComponent : public Component {
        public:
            StatsComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                TextComponent &highText,
                TextComponent &lowText,
                const std::vector<std::pair<std::string, std::string>> &stats
            );
            ~StatsComponent();

            void next() noexcept;
            void prev() noexcept;

        private:
            int _i = 0;
            TextComponent &_highText;
            TextComponent &_lowText;
            std::vector<std::pair<std::string, std::string>> _stats;
    };
}


#endif /* !STATS_HPP_ */

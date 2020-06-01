/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Stats
*/

#ifndef STATSCOMPONENT_HPP_
#define STATSCOMPONENT_HPP_

#include <vector>

#include "ECS/Component.hpp"
#include "Components/Text.hpp"

using namespace is::ecs;

namespace is::components
{
    class StatsComponent : public Component {
        public:
            StatsComponent(
                std::shared_ptr<is::ecs::Entity> &e,
                TextComponent &highText,
                TextComponent &lowText,
                std::vector<std::pair<std::string, std::string>> stats
            );
            ~StatsComponent() override;

            void next() noexcept;
            void prev() noexcept;

            void deleteComponent() override;
            void setContinue(bool c) noexcept;

            [[nodiscard]] bool isContinue() const noexcept;

        private:
            int _i = 0;
            TextComponent &_highText;
            TextComponent &_lowText;
            std::vector<std::pair<std::string, std::string>> _stats;
            bool _continue = false;
    };
}


#endif /* !STATS_HPP_ */

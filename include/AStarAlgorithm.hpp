/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AStarAlgorithm
*/

#ifndef ASTARALGORITHM_HPP_
#define ASTARALGORITHM_HPP_

#include <utility>
#include <vector>
#include <algorithm>
#include "Exception.hpp"
#include <cmath>
#include <functional>
#include <memory>
#include <stack>
#include <optional>

namespace is
{
    class AStarAlgorithm {
        private:
            struct Node
            {
                Node(
                    std::shared_ptr<Node> pparent,
                    std::pair<int, int> ppos,
                    double gg,
                    double hh,
                    double ff)
                    : parent(std::move(pparent)), pos(std::move(ppos)), g(gg), h(hh), f(ff)
                {};
                std::shared_ptr<Node> parent;
                std::pair<int, int> pos;
                double g;
                double h;
                double f;
                bool operator<(const Node &node) const
                {
                    return (f < node.f);
                }
                bool operator==(const Node &node) const
                {
                    return (node.pos == pos);
                }
            };

        public:
            AStarAlgorithm(
                int mapX,
                int mapY,
                const std::pair<int, int> &src,
                const std::pair<int, int> &dest,
                std::function<bool(const std::pair<int, int> &)> isBlock
            );

            ~AStarAlgorithm() = default;
            AStarAlgorithm(const AStarAlgorithm &astar) = delete;
            AStarAlgorithm &operator=(const AStarAlgorithm &astar) = delete;

            bool searchPath();
            const std::optional<std::pair<int, int>> getNextPos();

        private:
            void checkSuccessors(const std::shared_ptr<Node> &currentNode, const std::shared_ptr<Node> &endNode);
            [[nodiscard]] bool isValid(std::pair<int, int> cell) const noexcept;

        private:
            int _mapX;
            int _mapY;
            const std::pair<int, int> &_src;
            const std::pair<int, int> &_dest;
            std::vector<std::shared_ptr<Node>> _openList;
            std::vector<std::shared_ptr<Node>> _closeList;
            std::function<bool(const std::pair<int, int> &)> _isBlock;
            std::stack<std::pair<int, int>> _path;
    };
} // namespace is

#endif /* !ASTARALGORITHM_HPP_ */

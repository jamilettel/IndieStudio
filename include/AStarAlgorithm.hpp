/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AStarAlgorithm
*/

#ifndef ASTARALGORITHM_HPP_
#define ASTARALGORITHM_HPP_

#include <vector>
#include <algorithm>
#include "Exception.hpp"
#include <iostream>
#include <cmath>
#include <functional>
#include <memory>

// class Node
// {
//     public:
//         Node(std::shared_ptr<Node> parent, std::pair<int, int> pos, double g, double h, double f) : _parent(parent), _pos(pos), _g(g), _h(h), _f(f) {

//         };

//         ~Node() = default;
//         bool operator<(const Node &Node)
//         {
//             return (_f < Node._f);
//         };
//         std::shared_ptr<Node> parent() const noexcept
//         {
//             return (_parent);
//         };
//         const std::pair<int, int> &pos() const noexcept
//         {
//             return (_pos);
//         };
//         double g() const noexcept
//         {
//             return (_g);
//         };

//         double getF() const noexcept
//         {
//             return (_f);
//         };
//         double getH() const noexcept
//         {
//             return (_h);
//         };
//     private:
//         std::shared_ptr<Node> _parent;
//         std::pair<int, int> _pos;
//         double _g;
//         double _h;
//         double _f;
// };

namespace is
{
    template<typename T>
    class AStarAlgorithm {
        public:
            struct Node
            {
                Node(std::shared_ptr<Node> pparent, std::pair<int, int> ppos, double gg, double hh, double ff) : parent(pparent), pos(ppos), g(gg), h(hh), f(ff)
                {};
                std::shared_ptr<Node> parent;
                std::pair<int, int> pos;
                double g;
                double h;
                double f;
                bool operator<(const Node &node)
                {
                    return (f < node.f);
                }
            };

        public:
            AStarAlgorithm(
                std::vector<std::vector<T>> map,
                std::pair<int, int> src,
                std::pair<int, int> dest,
                std::function<bool(T)> fct)
                : _map(map), _src(src), _dest(dest), _isBlock(fct)
            {
                _row = map.size();
                // if (_row == 0)
                    // throw AStarAlgorithm("Invalid map size");
                _col = map[0].size();
                // if (!isValid(src) || !isValid(dest))
                    // throw AStarAlgorithm("Invalid position");
                searchPath();
            };

            ~AStarAlgorithm() = default;
            AStarAlgorithm(const AStarAlgorithm &astar) = delete;
            AStarAlgorithm &operator=(const AStarAlgorithm &astar) = delete;

            bool isValid(std::pair<int, int> cell)
            {
                return (cell.first >= 0 && cell.first < _row && cell.second >= 0 && cell.second < _col);
            }

            void searchPath()
            {
                std::shared_ptr<Node> startNode = std::make_shared<Node>(nullptr, _src, 0, 0, 0);
                std::shared_ptr<Node> endNode = std::make_shared<Node>(nullptr, _dest, 0, 0, 0);

                _openList.emplace_back(startNode);

                while (!_openList.empty()) {
                    auto ptr = std::min_element(_openList.begin(), _openList.end());
                    std::shared_ptr<Node> currentNode = *ptr;

                    _openList.erase(ptr);
                    _closeList.emplace_back(currentNode);

                    if (currentNode->pos.first == endNode->pos.first && currentNode->pos.second == endNode->pos.second) {
                        while (currentNode->parent) {
                            std::cout << "Pos X " << currentNode->pos.first << " and Y " << currentNode->pos.second << std::endl;
                            currentNode = currentNode->parent;
                        }
                        return;
                    }

                    std::pair<int, int> successors[4] = {
                        {currentNode->pos.first - 1, currentNode->pos.second},
                        {currentNode->pos.first, currentNode->pos.second - 1},
                        {currentNode->pos.first, currentNode->pos.second + 1},
                        {currentNode->pos.first + 1, currentNode->pos.second}
                    };

                    for (size_t i = 0; i < 4; i++) {
                        if (!isValid(successors[i]) || _isBlock(_map[successors[i].first][successors[i].second]))
                            continue;

                        if (std::find_if(_closeList.begin(), _closeList.end(), [&successors, &i](const std::shared_ptr<Node> &node) -> bool {
                            return (successors[i].first == node->pos.first && successors[i].second == node->pos.second);
                        }) != _closeList.end())
                            continue;
                        // std::cout << "Free " << successors[i].first << " " << successors[i].second << " " << isValid(successors[i]) << std::endl;
                        
                        double g = currentNode->g + 1;
                        double h = std::pow(successors[i].first - endNode->pos.first, 2) + std::pow(successors[i].second - endNode->pos.second, 2);
                        double f = g + h;

                        if (std::find_if(_openList.begin(), _openList.end(), [&successors, &i, &g](const std::shared_ptr<Node> &node) -> bool {
                            return (successors[i].first == node->pos.first && successors[i].second == node->pos.second && node->g < g);
                        }) != _openList.end())
                            continue;

                        std::shared_ptr<Node> node = std::make_shared<Node>(currentNode, successors[i], g, h, f);
                        _openList.emplace_back(node);
                    }
                }
            };

        private:
            std::vector<std::vector<T>> &_map;
            std::pair<int, int> &_src;
            std::pair<int, int> &_dest;
            int _col;
            int _row;
            std::vector<std::shared_ptr<Node>> _openList;
            std::vector<std::shared_ptr<Node>> _closeList;
            std::function<bool(T)> _isBlock;
    };
} // namespace is

#endif /* !ASTARALGORITHM_HPP_ */

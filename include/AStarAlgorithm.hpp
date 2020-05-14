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
#include <stack>

namespace is
{
    template<typename T>
    class AStarAlgorithm {
        private:
            struct Node
            {
                Node(
                    const std::shared_ptr<Node> &pparent,
                    const std::pair<int, int> &ppos,
                    double gg,
                    double hh,
                    double ff)
                    : parent(pparent), pos(ppos), g(gg), h(hh), f(ff)
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
                bool operator==(const Node &node)
                {
                    return (node.pos == pos);
                }
            };

        public:
            AStarAlgorithm(
                const std::vector<std::vector<T>> &map,
                const std::pair<int, int> &src,
                const std::pair<int, int> &dest,
                std::function<bool(const T &)> isBlock)
                : _map(map), _src(src), _dest(dest), _isBlock(isBlock)
            {
                _row = map.size();
                // if (_row == 0)
                    // throw AStarAlgorithm("Invalid map size");
                _col = map[0].size();
                // if (!isValid(src) || !isValid(dest))
                    // throw AStarAlgorithm("Invalid position");
            };

            ~AStarAlgorithm() = default;
            AStarAlgorithm(const AStarAlgorithm &astar) = delete;
            AStarAlgorithm &operator=(const AStarAlgorithm &astar) = delete;

            bool searchPath()
            {
                std::shared_ptr<Node> startNode = std::make_shared<Node>(nullptr, _src, 0, 0, 0);
                std::shared_ptr<Node> endNode = std::make_shared<Node>(nullptr, _dest, 0, 0, 0);

                _openList.emplace_back(startNode);

                while (!_openList.empty()) {

                    // Find in open list the node with the smallest f
                    auto ptr = std::min_element(_openList.begin(), _openList.end(), [](const std::shared_ptr<Node> &first, const std::shared_ptr<Node> &second) {
                        return (first->f < second->f);
                    });
                    std::shared_ptr<Node> currentNode = *ptr;

                    // Erase of the open list and place it in the close list
                    _openList.erase(ptr);
                    _closeList.emplace_back(currentNode);

                    // If we are arrive
                    if (*currentNode.get() == *endNode.get()) {
                        while (currentNode->parent) {
                            _path.push(currentNode->pos);
                            currentNode = currentNode->parent;
                        }
                        return (true);
                    }

                    checkSuccessors(currentNode, endNode);
                }
                return (false);
            };

            const std::optional<std::pair<int, int>> getNextPos()
            {
                std::optional<std::pair<int, int>> pos;

                if (!_path.size())
                    return (pos);
                pos.emplace(_path.top());
                _path.pop();
                return (pos);
            }

        private:

            void checkSuccessors(const std::shared_ptr<Node> &currentNode, const std::shared_ptr<Node> &endNode)
            {
                const std::pair<int, int> successors[4] = {
                    {currentNode->pos.first - 1, currentNode->pos.second},
                    {currentNode->pos.first, currentNode->pos.second - 1},
                    {currentNode->pos.first, currentNode->pos.second + 1},
                    {currentNode->pos.first + 1, currentNode->pos.second}
                };

                for (size_t i = 0; i < 4; i++) {
                    if (!isValid(successors[i]) || _isBlock(_map[successors[i].first][successors[i].second]))
                        continue;

                    // if in close list
                    if (std::find_if(_closeList.begin(), _closeList.end(), [&successors, &i](const std::shared_ptr<Node> &node) -> bool {
                        return (successors[i].first == node->pos.first && successors[i].second == node->pos.second);
                    }) != _closeList.end())
                        continue;

                    double g = currentNode->g + 1;
                    double h = std::pow(successors[i].first - endNode->pos.first, 2) + std::pow(successors[i].second - endNode->pos.second, 2);
                    double f = g + h;

                    // if in open list
                    if (std::find_if(_openList.begin(), _openList.end(), [&successors, &i, &f](const std::shared_ptr<Node> &node) -> bool {
                        return (successors[i].first == node->pos.first && successors[i].second == node->pos.second && node->f < f);
                    }) != _openList.end())
                        continue;
                    
                    _openList.emplace_back(std::make_shared<Node>(currentNode, successors[i], g, h, f));
                }
            }

            bool isValid(std::pair<int, int> cell)
            {
                return (cell.first >= 0 && cell.first < _row && cell.second >= 0 && cell.second < _col);
            }

        private:
            const std::vector<std::vector<T>> &_map;
            const std::pair<int, int> &_src;
            const std::pair<int, int> &_dest;
            int _col;
            int _row;
            std::vector<std::shared_ptr<Node>> _openList;
            std::vector<std::shared_ptr<Node>> _closeList;
            std::function<bool(const T &)> _isBlock;
            std::stack<std::pair<int, int>> _path;
    };
} // namespace is


/********************\
*
* Example of using AStarAlgorithm
*
\********************/

/*
bool isBlock(int cell)
{
    return (cell == 0);
}

int main(int argc, char const *argv[])
{
    std::vector<std::vector<int>> map = {
        { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1 }, 
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 }, 
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 }, 
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 }, 
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 }, 
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 }, 
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 }, 
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 1, 1, 1, 0, 1 }
    };
    std::pair<int, int> src = std::make_pair(8, 10);
    std::pair<int, int> dest = std::make_pair(0, 0);
    is::AStarAlgorithm<int> astar(map, src, dest, &isBlock);
    astar.searchPath();
    std::optional<std::pair<int, int>> pos;
    while ((pos = astar.getNextPos()).has_value()) {
        std::cout << "X :" << pos.value().first << " and Y:" << pos.value().second << std::endl;
    }
    return 0;
}
*/

#endif /* !ASTARALGORITHM_HPP_ */

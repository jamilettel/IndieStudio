/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AStarAlgorithm
*/

#include "AStarAlgorithm.hpp"

using namespace is;
using namespace is::exceptions;

AStarAlgorithm::AStarAlgorithm(
    int mapX,
    int mapY,
    const std::pair<int, int> &src,
    const std::pair<int, int> &dest,
    std::function<bool(const std::pair<int, int> &)> isBlock
) : _mapX(mapX), _mapY(mapY), _src(src), _dest(dest), _isBlock(isBlock)
{
    if (_mapX <= 0)
        throw AStarAlgorithmException("Invalid map size");
    if (_mapY <= 0)
        throw AStarAlgorithmException("Invalid map size");
    if (!isValid(src) || !isValid(dest))
        throw AStarAlgorithmException("Invalid position");
}

bool AStarAlgorithm::searchPath()
{
    std::shared_ptr<Node> startNode = std::make_shared<Node>(nullptr, _src, 0, 0, 0);
    std::shared_ptr<Node> endNode = std::make_shared<Node>(nullptr, _dest, 0, 0, 0);

    _openList.emplace_back(startNode);

    while (!_openList.empty()) {

        // Find in open list the node with the smallest f
        auto ptr = std::min_element(_openList.begin(),
                                    _openList.end(),
                                    [](const std::shared_ptr<Node> &first,
                                       const std::shared_ptr<Node> &second) {
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
}

const std::optional<std::pair<int, int>> AStarAlgorithm::getNextPos()
{
    std::optional<std::pair<int, int>> pos;

    if (!_path.size())
        return (pos);
    pos.emplace(_path.top());
    _path.pop();
    return (pos);
}

void AStarAlgorithm::checkSuccessors(const std::shared_ptr<Node> &currentNode, const std::shared_ptr<Node> &endNode)
{
    const std::pair<int, int> successors[4] = {
        {currentNode->pos.first - 1, currentNode->pos.second},
        {currentNode->pos.first, currentNode->pos.second - 1},
        {currentNode->pos.first, currentNode->pos.second + 1},
        {currentNode->pos.first + 1, currentNode->pos.second}
    };

    for (size_t i = 0; i < 4; i++) {
        if (!isValid(successors[i]) || _isBlock(successors[i]))
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

bool AStarAlgorithm::isValid(std::pair<int, int> cell) const noexcept
{
    return (cell.first >= 0 && cell.first < _mapX && cell.second >= 0 && cell.second < _mapY);
}

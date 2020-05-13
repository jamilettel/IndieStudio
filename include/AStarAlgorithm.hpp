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

namespace is
{
    template<typename T>
    class AStarAlgorithm {
        public:
            AStarAlgorithm(
                const std::vector<std::vector<T>> &map,
                const std::pair<int, int> &src,
                const std::pair<int, int> &dest)
                : _map(map), _src(src), _dest(dest)
            {
                _row = map.size();
                if (_row == 0)
                    throw AStarAlgorithm("Invalid map size");
                _col = map[0].size();
                if (!isValid(src) || !isValid(dest))
                    throw AStarAlgorithm("Invalid position");
                _openList.emplace_back(std::make_pair<int, int>(src.first, src.second));
                searchPath();
            };

            ~AStarAlgorithm() = default;
            AStarAlgorithm(const AStarAlgorithm &astar) = delete;
            AStarAlgorithm &operator=(const AStarAlgorithm &astar) = delete;

            // To pass as argument
            bool isBlock(T &cell)
            {
                return (true);
            }

        private:
            bool isValid(const std::pair<int, int> &cell)
            {
                return (cell.first >= 0 && cell.first < _row && cell.second >= 0 && cell.second < _col);
            }

            double calculateHeuristic();

            bool isDest()

            void searchPath()
            {
                std::pair<int, int> pos = *_openList.begin();

                _openList.erase(_openList.begin());
                _closeList.emplace_back(pos);
                if (isValid(pos)) {
                    if (pos == _dest) {
                        printf("FOUND");
                        return;
                    }
                }
            };


        private:
            std::vector<std::vector<T>> &_map;
            std::pair<int, int> &_src;
            std::pair<int, int> &_dest;
            int _col;
            int _row;
            std::vector<std::pair<int, int>> _openList;
            std::vector<std::pair<int, int>> _closeList;
    };
} // namespace is

#endif /* !ASTARALGORITHM_HPP_ */

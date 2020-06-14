/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Utils
*/

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <string>
#include <vector>

namespace is {

    class Utils {
    public:
        Utils() = delete;

        static bool loadFileInArray(const std::string &filePath, std::vector<std::string> &lines);

        static std::vector<std::string> strtok(std::string str, const std::string& sep);

        static bool isValidNum(const std::string &string);

    protected:
    private:
    };

}

#endif

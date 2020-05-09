/*
** EPITECH PROJECT, 2020
** IDGenerator.hpp
** File description:
** 
*/

#ifndef IDGENERATOR_HPP
#   define IDGENERATOR_HPP

#   include <sys/types.h>

class IDGenerator {
    public:
        static size_t id;
        static size_t getNewID();
};

#endif

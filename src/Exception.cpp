/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Exception
*/

#include "Exception.hpp"

is::exceptions::Exception::Exception(const std::string &component,
                                     const std::string &message):
_component(component),
_message(message)
{}

const char *is::exceptions::Exception::what() const noexcept
{
    return (_message.c_str());
}

const std::string &is::exceptions::Exception::getComponent() const
{
    return (_component);
}

is::exceptions::ECSException::ECSException(const std::string &message):
    is::exceptions::Exception("ECS", message)
{}

is::exceptions::AStarAlgorithmException::AStarAlgorithmException(const std::string &message):
    is::exceptions::Exception("AStarAlogrithm", message)
{}
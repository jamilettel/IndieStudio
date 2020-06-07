/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Exception
*/

#include "Exception.hpp"

#include <utility>

is::exceptions::Exception::Exception(std::string component,
                                     std::string message):
_component(std::move(component)),
_message(std::move(message))
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
    is::exceptions::Exception("AStarAlgorithm", message)
{}

is::exceptions::EventManagerException::EventManagerException(const std::string &message) :
is::exceptions::Exception("EventManager", message)
{
}

is::exceptions::WindowException::WindowException(const std::string &message) :
        is::exceptions::Exception("Window", message)
{
}

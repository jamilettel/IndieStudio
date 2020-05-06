/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Exceptions
*/

#ifndef INDIESTUDIO_EXCEPTIONS_HPP_
#define INDIESTUDIO_EXCEPTIONS_HPP_

#include <exception>
#include <string>

namespace is::exceptions {

    class Exception: public std::exception {
    public:
        Exception(const std::string &component, const std::string &message);
        ~Exception() = default;

        Exception(const Exception &) = default;
        Exception &operator=(const Exception &) = default;

        const char *what() const noexcept override;
        const std::string &getComponent() const;

    protected:
    private:
        std::string _component;
        std::string _message;
    };

    class ECSException: public Exception {
    public:
        ECSException(const std::string &message);
        ~ECSException() = default;

    protected:
    private:
    };

}

#endif /* !INDIESTUDIO_EXCEPTIONS_HPP_ */

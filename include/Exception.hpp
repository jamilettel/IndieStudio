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
            Exception(std::string component, std::string message);
            ~Exception() override = default;

            Exception(const Exception &) = default;
            Exception &operator=(const Exception &) = default;

            [[nodiscard]] const char *what() const noexcept override;
            [[nodiscard]] const std::string &getComponent() const;

        private:
            std::string _component;
            std::string _message;
    };

    class ECSException: public Exception {
        public:
            explicit ECSException(const std::string &message);
            ~ECSException() override = default;
    };

    class EventManagerException: public Exception {
        public:
            explicit EventManagerException(const std::string &message);
            ~EventManagerException() override = default;
    };

    class AStarAlgorithmException: public Exception {
        public:
            explicit AStarAlgorithmException(const std::string &message);
            ~AStarAlgorithmException() override = default;

        protected:
        private:
    };

}

#endif /* !INDIESTUDIO_EXCEPTIONS_HPP_ */

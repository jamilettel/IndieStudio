/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <vector>
#include <memory>
#include "ECS/Component.hpp"
#include <optional>
#include <uuid/uuid.h>
#include "Exception.hpp"

namespace is::ecs {

    class Entity {
    public:
        Entity();
        ~Entity() = default;

        Entity(const Entity &) = default;
        Entity &operator=(const Entity &) = default;

        template <class T>
        std::optional<std::weak_ptr<T>> getComponent() {
            std::optional<std::weak_ptr<T>> ret;

            for (std::shared_ptr<Component> &component: _components) {
                if (dynamic_cast<T *>(component.get())) {
                    ret.emplace(std::shared_ptr<T>(static_cast<T *>(component.get())));
                    break;
                }
            }
            return ret;
        }

        template <typename T, typename ...U>
        void addComponent(U &&...args) {
            if (getComponent<T>().has_value())
                throw is::exceptions::ECSException("Cannot add two components of same type to entity");
            _components.emplace_back(std::make_shared<T>(args...));
        }

    protected:
    private:
        uuid_t _uuid;
        bool _actif;
        std::vector<std::shared_ptr<Component>> _components;
        bool _delete;

    };

}

#endif /* !ENTITY_HPP_ */

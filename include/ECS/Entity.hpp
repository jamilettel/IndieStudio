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
#include "Exception.hpp"

namespace is::ecs {

    class Entity {
    public:
        Entity();
        ~Entity() = default;

        Entity(const Entity &) = default;
        Entity &operator=(const Entity &) = default;

        template <class T>
        std::optional<std::shared_ptr<T>> getComponent() {
            std::optional<std::shared_ptr<T>> ret;

            for (std::shared_ptr<Component> &component: _components) {
                if (dynamic_cast<T *>(component.get())) {
                    ret.emplace(std::dynamic_pointer_cast<T>(component));
                    break;
                }
            }
            return ret;
        }

        std::vector<std::shared_ptr<Component>> getComponents() const;

        template <class T>
        std::vector<std::shared_ptr<T>> getComponentsOfType() {
            std::vector<std::shared_ptr<T>> ret;

            for (std::shared_ptr<Component> &component: _components) {
                if (dynamic_cast<T *>(component.get()))
                    ret.emplace_back(std::shared_ptr<T>(static_cast<T *>(component.get())));
            }
            return ret;
        }


        template <typename T, typename ...U>
        void addComponent(U &&...args) {
            _components.emplace_back(std::make_shared<T>(args...));
        }

        void setDelete(bool set);
        bool shouldBeDeleted() const;

        bool isActive() const;
        void setActive(bool active);

    protected:
    private:
        int _id;
        bool _active;
        std::vector<std::shared_ptr<Component>> _components;
        bool _delete;

    };

}

#endif /* !ENTITY_HPP_ */

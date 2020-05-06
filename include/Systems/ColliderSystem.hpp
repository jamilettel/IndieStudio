/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ColliderSystem
*/

#ifndef COLLIDERSYSTEM_HPP_
#define COLLIDERSYSTEM_HPP_

#include "ECS/ASystem.hpp"

namespace is::system {

    class ColliderSystem: public is::ecs::ASystem {
    public:
        ColliderSystem() = default;
        ~ColliderSystem() = default;

        ColliderSystem(const ColliderSystem &) = default;
        ColliderSystem &operator=(const ColliderSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

    protected:
    private:
    };

}

#endif /* !COLLIDERSYSTEM_HPP_ */

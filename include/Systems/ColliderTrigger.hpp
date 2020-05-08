/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Collider Trigger
*/

#ifndef COLLIDERTRIGGERSYSTEM_HPP_
#define COLLIDERTRIGGERSYSTEM_HPP_

#include "Systems/Collider.hpp"

namespace is::systems {

    class ColliderTriggerSystem: public is::ecs::ASystem {
    public:
        ColliderTriggerSystem() = default;
        ~ColliderTriggerSystem() = default;

        ColliderTriggerSystem(const ColliderTriggerSystem &) = default;
        ColliderTriggerSystem &operator=(const ColliderTriggerSystem &) = default;

        void awake() override;
        void start() override;
        void update() override;
        void stop() override;
        void onTearDown() override;

    };

}

#endif /* !COLLIDERTRIGGERSYSTEM_HPP_ */

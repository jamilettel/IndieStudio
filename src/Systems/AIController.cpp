/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** AIController
*/

#include "Systems/AIController.hpp"

using namespace is::systems;
using namespace is::components;
using namespace is::ecs;

void AIControllerSystem::awake()
{
     std::vector<std::shared_ptr<Component>> &aiComponents =
        _componentManager->getComponentsByType(typeid(AIControllerComponent).hash_code());

    for (std::shared_ptr<Component> &component: aiComponents) {
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());
        
        ai.getInputManager().addValue("MoveHorizontalAxis", 0);
        ai.getInputManager().addValue("MoveVerticalAxis", 0);
        ai.getInputManager().addValue("Jump", 0);
        ai.getInputManager().addValue("DropBomb", 0);
    }
}

void AIControllerSystem::start()
{
    std::vector<std::shared_ptr<Component>> &time =
        _componentManager->getComponentsByType(typeid(TimeComponent).hash_code());

    if (!time.size())
        throw is::exceptions::Exception("Movement", "No time component in scene");
    _time.emplace(*static_cast<TimeComponent *>(time[0].get()));
}

void AIControllerSystem::stop()
{}

void AIControllerSystem::onTearDown()
{}

void AIControllerSystem::update()
{
    std::vector<std::shared_ptr<Component>> &aiComponents =
        _componentManager->getComponentsByType(typeid(AIControllerComponent).hash_code());

    for (std::shared_ptr<Component> &component: aiComponents) {
        AIControllerComponent &ai = *static_cast<AIControllerComponent *>(component.get());
        ai.timeBeforeBegin -= _time->get().getCurrentIntervalSeconds();
        if (ai.timeBeforeBegin > 0)
            continue;
        TransformComponent &tr = *static_cast<TransformComponent *>(ai.getEntity()->getComponent<TransformComponent>()->get());

        if (ai.needObjective) {
            ai.objective = irr::core::vector2df(0, 0);
            ai.needObjective = false;
        }

        // drop bomb when ia is stopped
        if (ai.getEntity()->getComponent<MovementComponent>()->get()->velocity == irr::core::vector3df(0)) {
            ai.getInputManager().setValue("DropBomb", 1);
        }

        // go objective
        if (!ai.lock.X) {
            if (tr.position.Z > ai.objective.X + 1.5)
                ai.getInputManager().setValue("MoveHorizontalAxis", -1);
            else if (tr.position.Z < ai.objective.X - 1.5)
                ai.getInputManager().setValue("MoveHorizontalAxis", 1);
            else {
                ai.getInputManager().setValue("MoveHorizontalAxis", 0);
                ai.lock.X = 1;
            }
        }

        if (!ai.lock.Y && ai.lock.X) {
            if (tr.position.X > ai.objective.Y + 1.5)
                ai.getInputManager().setValue("MoveVerticalAxis", -1);
            else if (tr.position.X < ai.objective.Y - 1.5)
                ai.getInputManager().setValue("MoveVerticalAxis", 1);
            else {
                ai.getInputManager().setValue("MoveHorizontalAxis", 0);
                ai.lock.Y = 1;
            }
        }

        //std::cout << tr.position.X << " " << tr.position.Z << std::endl;
        std::cout << ai.getInputManager().getInput("MoveHorizontalAxis") << " " << ai.getInputManager().getInput("MoveVerticalAxis") << std::endl;
    }
}

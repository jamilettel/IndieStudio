/*
** EPITECH PROJECT, 2020
** test.hpp
** File description:
** 
*/

#ifndef TEST_HPP
#   define TEST_HPP

#include "ECS/AScene.hpp"
#include "Systems/Window.hpp"
#include "Systems/Camera.hpp"
#include "Systems/Time.hpp"
#include "Systems/Button.hpp"
#include "Systems/Text.hpp"
#include "Systems/Slider.hpp"
#include "Systems/Image.hpp"

namespace is::scenes {

    class test : public is::ecs::AScene {
        public:
            test() : AScene(is::ecs::NOTHING){
    _entityManager = std::make_shared<is::ecs::EntityManager>();
    _componentManager = std::make_shared<is::ecs::ComponentManager>();
    _systemManager = std::make_shared<is::ecs::SystemManager>(_componentManager, _entityManager);
            }
            void initSystems()
{
    _systemManager->addSystem(std::make_shared<is::systems::TimeSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::WindowSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::CameraSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ButtonSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::TextSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::SliderSystem>());
    _systemManager->addSystem(std::make_shared<is::systems::ImageSystem>());
};
            void initEntities() {};
    };
}

#endif

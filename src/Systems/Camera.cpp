/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CameraSystem
*/

#include "Systems/Camera.hpp"

using namespace irr;

void is::systems::CameraSystem::awake()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::CameraComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        auto ptr = std::dynamic_pointer_cast<is::components::CameraComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("CameraSystem", "Could not get CameraComponent pointer");
        for (auto &cw : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
            auto ptr_window = std::dynamic_pointer_cast<is::components::WindowComponent>(cw);
            if (!ptr_window)
                throw is::exceptions::Exception("CameraSystem", "Could not get WindowComponent pointer");
            if (ptr->windowName != ptr_window->windowName)
                continue;
            ptr->node = ptr_window->scenemgr->addCameraSceneNode(0, ptr->position, ptr->rotation);
        }
    }
}

void is::systems::CameraSystem::start()
{

}

void is::systems::CameraSystem::update()
{
    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::CameraComponent).hash_code())) {
        std::vector<irr::core::vector2df> points;
        irr::core::vector2df centroid = {0, 0};
        double signedArea = 0.0;
        double x0 = 0.0;
        double y0 = 0.0;
        double x1 = 0.0;
        double y1 = 0.0;
        double a = 0.0;
        int i=0;
        
        auto ptr = std::dynamic_pointer_cast<is::components::CameraComponent>(elem);
        if (!ptr)
            throw is::exceptions::Exception("CameraSystem", "Could not get CameraComponent pointer");
        if (!ptr->gameCamera)
            continue;
        for (auto &ccc : _componentManager->getComponentsByType(typeid(is::components::CharacterControllerComponent).hash_code())) {
            auto ptr_char = std::dynamic_pointer_cast<is::components::CharacterControllerComponent>(ccc);
            if (!ptr_char)
                throw is::exceptions::Exception("CameraSystem", "Could not get CharacterControllerComponent pointer");
            irr::core::vector3df pos = ptr_char->getEntity()->getComponent<is::components::TransformComponent>()->get()->position;
            points.push_back({pos.X, pos.Z});
        }
        if (points.size() <= 0)
            continue;
        for (i=0; i<points.size()-1; ++i)
        {
            x0 = points[i].X;
            y0 = points[i].Y;
            x1 = points[i+1].X;
            y1 = points[i+1].Y;
            a = x0*y1 - x1*y0;
            signedArea += a;
            centroid.X += (x0 + x1)*a;
            centroid.Y += (y0 + y1)*a;
        }

        x0 = points[i].X;
        y0 = points[i].Y;
        x1 = points[0].X;
        y1 = points[0].Y;
        a = x0*y1 - x1*y0;
        signedArea += a;
        centroid.X += (x0 + x1)*a;
        centroid.Y += (y0 + y1)*a;

        signedArea *= 0.5;
        centroid.X /= (6.0*signedArea);
        centroid.Y /= (6.0*signedArea);

        ptr->node->setTarget(irr::core::vector3df(centroid.X, ptr->node->getTarget().Y, centroid.Y));
        ptr->node->setPosition(irr::core::vector3df(centroid.X - 15, ptr->node->getPosition().Y, centroid.Y));
    }
}

void is::systems::CameraSystem::stop()
{

}

void is::systems::CameraSystem::onTearDown()
{

}


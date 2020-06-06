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
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::CameraComponent).hash_code())) {
        if (elem->getEntity()->isInit())
            continue;
        const auto &ptr = static_cast<is::components::CameraComponent*>(elem.get());
        for (auto &cw : _componentManager->getComponentsByType(typeid(is::components::WindowComponent).hash_code())) {
            const auto &ptr_window = static_cast<is::components::WindowComponent*>(cw.get());
            if (ptr->windowName != ptr_window->windowName)
                continue;
            ptr->node = ptr_window->scenemgr->addCameraSceneNode(0, ptr->position, ptr->rotation);
            //std::cout << "X :" << ptr->node->getTarget().X << " Y : " << ptr->node->getTarget().Y << " Z : " << ptr->node->getTarget().Z << std::endl;
        }
    }
}

void is::systems::CameraSystem::start()
{

}

void is::systems::CameraSystem::update()
{
    static bool target = false;

    for (auto &elem : _componentManager->getComponentsByType(typeid(is::components::CameraComponent).hash_code())) {
        std::vector<irr::core::vector2df> points;
        irr::core::vector2df centroid = {0, 0};
        double signedArea = 0.0;
        double x0 = 0.0;
        double y0 = 0.0;
        double x1 = 0.0;
        double y1 = 0.0;
        double a = 0.0;
        size_t i = 0;

        auto ptr = static_cast<is::components::CameraComponent*>(elem.get());
        if (!ptr)
            throw is::exceptions::Exception("CameraSystem", "Could not get CameraComponent pointer");
        if (!ptr->gameCamera)
            continue;
        for (const auto &ccc : _componentManager->getComponentsByType(typeid(is::components::CharacterControllerComponent).hash_code())) {
            const auto &ptr_char = static_cast<is::components::CharacterControllerComponent*>(ccc.get());
            if (!ptr_char)
                throw is::exceptions::Exception("CameraSystem", "Could not get CharacterControllerComponent pointer");
            const auto &ptr_tr = ptr_char->getEntity()->getComponent<is::components::TransformComponent>();
            if (!ptr_tr)
                throw is::exceptions::Exception("CameraSystem", "Could not get TransformComponent pointer");
            irr::core::vector3df pos = ptr_tr->get()->position;

            points.push_back({pos.X, pos.Z});
        }
        if (points.size() <= 0)
            continue;
        else if (points.size() == 1) {
            centroid.X = points[0].X;
            centroid.Y = points[0].Y;
        }
        else if (points.size() == 2) {
            centroid.X = (points[0].X + points[1].X) / 2;
            centroid.Y = (points[0].Y + points[1].Y) / 2;
        }
        else {
            for (i = 0; i < points.size() - 1; i++) {
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
            a = x0 * y1 - x1 * y0;
            signedArea += a;
            centroid.X += (x0 + x1)*a;
            centroid.Y += (y0 + y1)*a;
            signedArea *= 0.5;
            centroid.X /= (6.0*signedArea);
            centroid.Y /= (6.0*signedArea);
        }
        irr::core::vector3df pos = ptr->node->getPosition();
        irr::core::vector2df npos;

        pos.X += 15;
        if (centroid.X > pos.X - 0.05f)
            npos.X = pos.X + 0.02f;
        else if (centroid.X < pos.X + 0.05f)
            npos.X = pos.X - 0.02f;
        if (centroid.Y < pos.Z + 0.05f)
            npos.Y = pos.Z - 0.02f;
        else if (centroid.Y > pos.Z - 0.05f)
            npos.Y = pos.Z + 0.02f;
        if (target)
            ptr->node->setTarget(irr::core::vector3df(npos.X - 3, ptr->node->getTarget().Y, npos.Y));
        else
            ptr->node->setPosition(irr::core::vector3df(npos.X - 15, ptr->node->getPosition().Y, npos.Y));

    }
    target = !target;
}

void is::systems::CameraSystem::stop()
{
    for (const auto &elem : _componentManager->getComponentsByType(typeid(is::components::CameraComponent).hash_code())) {
        const auto &ptr = static_cast<is::components::CameraComponent*>(elem.get());

        ptr->node->setPosition(irr::core::vector3df(-15, 27, 0));
        ptr->node->setRotation(irr::core::vector3df(-3, 0, 0));
        ptr->node->setTarget(irr::core::vector3df(-3, 0, 0));
    }
}

void is::systems::CameraSystem::onTearDown()
{

}

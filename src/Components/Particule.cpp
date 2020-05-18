/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Particule
*/

#include "Components/Particule.hpp"
#include "IDGenerator.hpp"

using namespace irr;

void wickParticule(scene::IParticleSystemSceneNode *element, const std::shared_ptr<is::components::WindowComponent>& ptr_window)
{
    auto e = element->createBoxEmitter(
        irr::core::aabbox3d<irr::f32>(-1, 0, -1, 1, 0, 1),
            irr::core::vector3df(0, 0.002f, 0),
            10, 20,
            irr::video::SColor(0, 50, 50, 50),
            irr::video::SColor(0, 100, 100, 100),
            600, 1000,
            0,
            irr::core::dimension2df(0.3, 0.3),
            irr::core::dimension2df(0.5, 0.5));
    element->setEmitter(e);
    e->drop();
    element->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}

#include <iostream>
void fireParticule(scene::IParticleSystemSceneNode *element, const std::shared_ptr<is::components::WindowComponent>& ptr_window)
{
    auto e = element->createSphereEmitter(irr::core::vector3df(0, 0, 0),
3,
            irr::core::vector3df(0.00, 0.001, 0.00),
            200, 300,
            irr::video::SColor(0, 255, 0, 0),
            irr::video::SColor(0, 255, 50, 0),
            600, 1000,
            180,
            irr::core::dimension2df(0.8, 0.8),
            irr::core::dimension2df(0.9, 0.9));
    element->setEmitter(e);
    e->drop();
    element->setMaterialFlag(irr::video::EMF_LIGHTING, false);
}


std::map<is::components::PARTICULE, particuleFunction> particuleMap = 
{
    {is::components::WICK, wickParticule},
    {is::components::FIRE, fireParticule}
};

is::components::ParticuleComponent::ParticuleComponent(std::shared_ptr<is::ecs::Entity> &e,std::string wn, core::vector3df position, is::components::PARTICULE particule) :
    Component(e), windowName(std::move(wn)), _position(position), _particule(particule)
{
}

void is::components::ParticuleComponent::init(const std::shared_ptr<is::components::WindowComponent>& ptr_window)
{
    element = ptr_window->scenemgr->addParticleSystemSceneNode(true, 0, -1, _position,
        irr::core::vector3df(0, 0, 0), irr::core::vector3df(0.5, 0.5, 0.5));
    
    if (!element)
        throw is::exceptions::Exception("ParticuleComponent", "Could not create bode from model");
    particuleMap[_particule](element, ptr_window);
 }

void is::components::ParticuleComponent::deleteComponent()
{
    element->remove();
}

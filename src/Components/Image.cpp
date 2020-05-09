/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Image
*/

#include "Components/Image.hpp"
#include "IDGenerator.hpp"

using namespace irr;


is::components::ImageComponent::ImageComponent(std::shared_ptr<is::ecs::Entity> &e,
    const std::string &filename, const std::string &wn, int x, int y) :
Component(e), windowName(wn), _dimension(x, y), _filename(filename) 
{
}

void is::components::ImageComponent::init(std::shared_ptr<is::components::WindowComponent> ptr_window)
{
    element = ptr_window->canvas->addImage(ptr_window->driver->getTexture(_filename.c_str()), _dimension, false, 0, IDGenerator::getNewID(), L"ui");
    if (!element)
        throw new is::exceptions::Exception("ImageCompononent", "Could not create node from model");
}

void is::components::ImageComponent::deleteComponent()
{
    element->remove();
}

/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Image
*/

#include "Components/Image.hpp"

#include <utility>
#include "IDGenerator.hpp"

using namespace is::components;
using namespace irr;

is::components::ImageComponent::ImageComponent(
    std::shared_ptr<is::ecs::Entity> &e,
    std::string filename,
    std::string wn,
    int x,
    int y,
    bool scale,
    bool visible
    ):
    GUIElementComponent(e),
    windowName(std::move(wn)),
    _dimension(x, y),
    _filename(std::move(filename)),
    _scale(scale),
    _visible(visible)
{
}

void is::components::ImageComponent::init(std::shared_ptr<is::components::WindowComponent> &ptr_window)
{
    _window = ptr_window;
    element = ptr_window->canvas->addImage(ptr_window->driver->getTexture(_filename.c_str()), _dimension, false, nullptr, IDGenerator::getNewID(), L"ui");
    if (!element)
        throw is::exceptions::Exception("ImageCompononent", "Could not create node from model");
    if (_scale) {
        element->setAlignment(gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE, gui::EGUIA_SCALE);
        element->setScaleImage(true);
    }
    element->setUseAlphaChannel(true);
    element->setVisible(_visible);
}

void is::components::ImageComponent::setPosition(float x, float y)
{
    element->setRelativePosition(irr::core::vector2di(x, y));
}

void is::components::ImageComponent::deleteComponent()
{
    element->remove();
}

void is::components::ImageComponent::bringToFront()
{
    if (element)
        _window->canvas->getRootGUIElement()->bringToFront(element);
}

void ImageComponent::setVisible(bool visible)
{
    if (visible != _visible) {
        _visible = visible;
        element->setVisible(visible);
    }
}

void ImageComponent::setImage(video::ITexture *image)
{
    element->setImage(image);
}

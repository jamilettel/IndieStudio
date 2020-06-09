/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Image
*/

#include "Components/Image.hpp"
#include "IDGenerator.hpp"
#include "Game.hpp"

using namespace is::components;
using namespace is::ecs;

ImageComponent::ImageComponent(
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

void ImageComponent::init(std::shared_ptr<WindowComponent> &ptr_window)
{
    _window = ptr_window;
    element = ptr_window->canvas->addImage(static_cast<irr::video::ITexture *>(is::Game::getResource(_filename)),
                                           _dimension,
                                           false,
                                           nullptr,
                                           IDGenerator::getNewID(),
                                           L"ui");
    if (!element)
        throw is::exceptions::Exception("ImageComponent", "Could not create node from model");
    if (_scale) {
        element->setAlignment(irr::gui::EGUIA_SCALE,
                              irr::gui::EGUIA_SCALE,
                              irr::gui::EGUIA_SCALE,
                              irr::gui::EGUIA_SCALE);
        element->setScaleImage(true);
    }
    element->setUseAlphaChannel(true);
    element->setVisible(_visible);
}

void ImageComponent::setPosition(float x, float y)
{
    _dimension.X = x;
    _dimension.Y = y;
    element->setRelativePosition(irr::core::vector2di(x, y));
}

const irr::core::vector2d<int> &ImageComponent::getPosition() const
{
    return _dimension;
}

void ImageComponent::deleteComponent()
{
    element->remove();
}

void ImageComponent::bringToFront()
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

void ImageComponent::setImage(irr::video::ITexture *image)
{
    element->setImage(image);
}

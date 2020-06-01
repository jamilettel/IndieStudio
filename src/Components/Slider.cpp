/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Slider
*/

#include "Components/Slider.hpp"
#include "IDGenerator.hpp"

using namespace is::ecs;
using namespace is::components;

is::components::SliderComponent::SliderComponent(std::shared_ptr<is::ecs::Entity> &e,
    std::string slider, std::string wn,
    int min, int max, int step, irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height) :
    Component(e), windowName(std::move(wn)), _dimension(x, y, x + width, y + height), _slider(std::move(slider)),
    _min(min), _max(max), _step(step)
{
}

void is::components::SliderComponent::init(const std::shared_ptr<is::components::WindowComponent>& ptr_window)
{
    elementSlider = ptr_window->canvas->addButton(irr::core::rect<irr::s32>(_dimension.UpperLeftCorner.X, _dimension.UpperLeftCorner.Y, _dimension.UpperLeftCorner.X + (_dimension.getWidth() / _step), _dimension.UpperLeftCorner.Y + _dimension.getHeight()), 0, IDGenerator::getNewID(), L"");
    if (!elementSlider)
        throw is::exceptions::Exception("SliderComponent", "Could not create bode from model");
}

void is::components::SliderComponent::setPosition(float position)
{
    elementSlider->setRelativePosition(irr::core::vector2di(position - (float)(_dimension.getWidth() / _step / 2), _dimension.UpperLeftCorner.Y));
    if (elementSlider->getRelativePosition().UpperLeftCorner.X < _dimension.UpperLeftCorner.X)
        elementSlider->setRelativePosition(irr::core::vector2di(_dimension.UpperLeftCorner.X, _dimension.UpperLeftCorner.Y));
    else if (elementSlider->getRelativePosition().UpperLeftCorner.X > _dimension.UpperLeftCorner.X + _dimension.getWidth())
        elementSlider->setRelativePosition(irr::core::vector2di(_dimension.UpperLeftCorner.X + _dimension.getWidth(), _dimension.UpperLeftCorner.Y));
}

bool is::components::SliderComponent::isPressed() const
{
    return (elementSlider->isPressed());
}

int is::components::SliderComponent::getStep() const
{
    float i = elementSlider->getRelativePosition().UpperLeftCorner.X - _dimension.UpperLeftCorner.X;
    return (i / _dimension.getWidth()) * _step;
}

void is::components::SliderComponent::deleteComponent()
{
    elementSlider->remove();
}

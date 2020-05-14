/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Audio
*/

#ifndef SLIDERCOMPONENT_HPP_
#define SLIDERCOMPONENT_HPP_

#include <vector>
#include "ECS/Component.hpp"
#include <memory>
#include <irrlicht.h>
#include "Components/Window.hpp"
#include "Components/Button.hpp"
#include "Components/Image.hpp"
#include "Exception.hpp"

namespace is::components {
    class SliderComponent: public is::ecs::Component {
        public:
            SliderComponent(std::shared_ptr<is::ecs::Entity> &e, std::string slider, std::string wn, int min, int max, int step,
                    irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height);
            ~SliderComponent() override = default;

            SliderComponent(const SliderComponent &) = delete;
            SliderComponent &operator=(const SliderComponent &) = delete;

            void init(const std::shared_ptr<is::components::WindowComponent>& ptr_window);
            void deleteComponent() override;

            void setPosition(float position);
            [[nodiscard]] bool isPressed() const;
            [[nodiscard]] int getStep() const;
            std::string windowName;
        private:
            irr::core::rect<irr::s32> _dimension;
            std::string _slider;
            int _min;
            int _max;
            int _step;
            irr::gui::IGUIButton *elementSlider{};
            irr::gui::IGUIStaticText *elementFrame{};
    };

}

#endif /* !BUTTONCOMPONENT_HPP_ */

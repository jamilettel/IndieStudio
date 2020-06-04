/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** NumberField
*/

#ifndef NUMBERFIELDCOMPONENT_HPP_
#define NUMBERFIELDCOMPONENT_HPP_

#include "ECS/Component.hpp"
#include "Components/Button.hpp"
#include "Components/Image.hpp"
#include "Components/Text.hpp"

namespace is::components {

    class NumberFieldComponent: public ecs::Component {
    public:
        NumberFieldComponent(
            std::shared_ptr<ecs::Entity> &e
            );
        ~NumberFieldComponent() = default;

        NumberFieldComponent(const NumberFieldComponent &) = delete;
        NumberFieldComponent &operator=(const NumberFieldComponent &) = delete;

        void deleteComponent() override;

        int getEnteredNumber() const;

        void changeNumber(int pos, int amout);

    private:
        void initOneComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            // ButtonComponent *&buttonDown,
            // ButtonComponent *&buttonUp,
            // ImageComponent *&image,
            // TextComponent *&text,
            int num);

    private:
        std::vector<ButtonComponent*> _buttonDown;
        std::vector<ButtonComponent*> _buttonUp;
        std::vector<ImageComponent*> _image;
        std::vector<TextComponent*> _text;
        std::vector<int> _numbers;
    };

}

#endif /* !NUMBERFIELDCOMPONENT_HPP_ */

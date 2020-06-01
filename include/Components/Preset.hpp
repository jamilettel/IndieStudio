/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** Preset
*/

#ifndef PRESETCOMPONENT_HPP_
#define PRESETCOMPONENT_HPP_

#include "Components/KeyboardPreset.hpp"
#include "Components/JoystickPreset.hpp"
#include "Components/Image.hpp"
#include "Text.hpp"

#ifndef RESOURCES_PATH
#define RESOURCES_PATH "./resources/"
#endif
#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str))

namespace is::components {

    class KeyboardPresetComponent;

    class PresetComponent : public is::ecs::Component {

    public:
        typedef struct {
            irr::EKEY_CODE _key;
            std::string _name;
        } EquivalentKey;

        typedef struct {
            int _button;
            std::string _filename;
        } EquivalentButton;

        static inline const EquivalentKey EquivalentKeys[] = {
            {irr::EKEY_CODE::KEY_KEY_B, "B"},
            {irr::EKEY_CODE::KEY_KEY_A, "A"},
            {irr::EKEY_CODE::KEY_KEY_C, "C"},
            {irr::EKEY_CODE::KEY_KEY_D, "D"},
            {irr::EKEY_CODE::KEY_KEY_E, "E"},
            {irr::EKEY_CODE::KEY_KEY_F, "F"},
            {irr::EKEY_CODE::KEY_KEY_G, "G"},
            {irr::EKEY_CODE::KEY_KEY_H, "H"},
            {irr::EKEY_CODE::KEY_KEY_I, "I"},
            {irr::EKEY_CODE::KEY_KEY_J, "J"},
            {irr::EKEY_CODE::KEY_KEY_K, "K"},
            {irr::EKEY_CODE::KEY_KEY_L, "L"},
            {irr::EKEY_CODE::KEY_KEY_M, "M"},
            {irr::EKEY_CODE::KEY_KEY_N, "N"},
            {irr::EKEY_CODE::KEY_KEY_O, "O"},
            {irr::EKEY_CODE::KEY_KEY_P, "P"},
            {irr::EKEY_CODE::KEY_KEY_Q, "Q"},
            {irr::EKEY_CODE::KEY_KEY_R, "R"},
            {irr::EKEY_CODE::KEY_KEY_S, "S"},
            {irr::EKEY_CODE::KEY_KEY_T, "T"},
            {irr::EKEY_CODE::KEY_KEY_U, "U"},
            {irr::EKEY_CODE::KEY_KEY_V, "V"},
            {irr::EKEY_CODE::KEY_KEY_W, "W"},
            {irr::EKEY_CODE::KEY_KEY_X, "X"},
            {irr::EKEY_CODE::KEY_KEY_Y, "Y"},
            {irr::EKEY_CODE::KEY_KEY_Z, "Z"},
            {irr::EKEY_CODE::KEY_KEY_1, "1"},
            {irr::EKEY_CODE::KEY_KEY_2, "2"},
            {irr::EKEY_CODE::KEY_KEY_3, "3"},
            {irr::EKEY_CODE::KEY_KEY_4, "4"},
            {irr::EKEY_CODE::KEY_KEY_5, "5"},
            {irr::EKEY_CODE::KEY_KEY_6, "6"},
            {irr::EKEY_CODE::KEY_KEY_7, "7"},
            {irr::EKEY_CODE::KEY_KEY_8, "8"},
            {irr::EKEY_CODE::KEY_KEY_9, "9"},
            {irr::EKEY_CODE::KEY_SPACE, "Space"},
            {irr::EKEY_CODE::KEY_CONTROL, "Ctrl"},
            {irr::EKEY_CODE::KEY_SHIFT, "Shift"},
            {irr::EKEY_CODE::KEY_SPACE, "Space"},
            {irr::EKEY_CODE::KEY_DOWN, "Arrow Down"},
            {irr::EKEY_CODE::KEY_UP, "Arrow Up"},
            {irr::EKEY_CODE::KEY_RIGHT, "Arrow Right"},
            {irr::EKEY_CODE::KEY_LEFT, "Arrow Left"},
            {irr::EKEY_CODE::KEY_KEY_CODES_COUNT, "Unknown"},
        };

        static inline const EquivalentButton EquivalentButtons[] = {
            {0, RESSOURCE("ui/Controllers/LS_RIGHT.png")},
            {1, RESSOURCE("ui/Controllers/LS_UP.png")},
            {2, RESSOURCE("ui/Controllers/LS_BUTTON.png")},
            {3, RESSOURCE("ui/Controllers/RS_LEFT.png")},
            {4, RESSOURCE("ui/Controllers/RS_DOWN.png")},
            {5, RESSOURCE("ui/Controllers/RS_BUTTON.png")},
            {-1, RESSOURCE("ui/Controllers/A_BUTTON.png")},
            {-2, RESSOURCE("ui/Controllers/B_BUTTON.png")},
            {-3, RESSOURCE("ui/Controllers/X_BUTTON.png")},
            {-4, RESSOURCE("ui/Controllers/Y_BUTTON.png")},
            {-5, RESSOURCE("ui/Controllers/LB.png")},
            {-6, RESSOURCE("ui/Controllers/RB.png")},
            {-7, RESSOURCE("ui/Controllers/BACK_BUTTON.png")},
            {-8, RESSOURCE("ui/Controllers/START_BUTTON.png")},
            {-9, RESSOURCE("ui/Controllers/HOME_BUTTON.png")},
            {-10, RESSOURCE("ui/Controllers/RS_BUTTON.png")},
            {-11, RESSOURCE("ui/Controllers/LS_BUTTON.png")},
            {-9999, RESSOURCE("")},
        };

    public:
        explicit PresetComponent(
            std::shared_ptr<is::ecs::Entity> &e,
            int number = 0
            );
        ~PresetComponent() override = default;

        PresetComponent(const PresetComponent &) = delete;
        PresetComponent &operator=(const PresetComponent &) = delete;

        void deleteComponent() override;

        [[nodiscard]] KeyboardPresetComponent &getKeyboardPreset();
        [[nodiscard]] JoystickPresetComponent &getJoystickPreset();

        static std::string getEquivalentKey(irr::EKEY_CODE key);
        static std::string getEquivalentButton(int button);

        std::vector<std::reference_wrapper<TextComponent>> _textPreset;
        std::vector<std::reference_wrapper<ImageComponent>> _imagePreset;
        std::vector<std::reference_wrapper<ButtonComponent>> _buttonPreset;

    private:
        KeyboardPresetComponent _keyboardPreset;
        JoystickPresetComponent _joystickPreset;

    public:
        int presetNumber;
        std::optional<PresetAction> _toChange;
        std::optional<std::tuple<std::reference_wrapper<TextComponent>, std::reference_wrapper<ImageComponent>, std::reference_wrapper<ButtonComponent>>> _toChangeUI;
        bool _onSelect;
        int _callerID;
    };

}

#endif /* !PRESETCOMPONENT_HPP_ */

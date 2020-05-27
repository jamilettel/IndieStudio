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
#include <vector>
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
            EKEY_CODE _key;
            std::string _name;
        } EquivalentKey;

        typedef struct {
            int _button;
            std::string _filename;
        } EquivalentButton;

        static inline const EquivalentKey EquivalentKeys[] = {
            {EKEY_CODE::KEY_KEY_A, "A"},
            {EKEY_CODE::KEY_KEY_B, "B"},
            {EKEY_CODE::KEY_KEY_C, "C"},
            {EKEY_CODE::KEY_KEY_D, "D"},
            {EKEY_CODE::KEY_KEY_E, "E"},
            {EKEY_CODE::KEY_KEY_F, "F"},
            {EKEY_CODE::KEY_KEY_G, "G"},
            {EKEY_CODE::KEY_KEY_H, "H"},
            {EKEY_CODE::KEY_KEY_I, "I"},
            {EKEY_CODE::KEY_KEY_J, "J"},
            {EKEY_CODE::KEY_KEY_K, "K"},
            {EKEY_CODE::KEY_KEY_L, "L"},
            {EKEY_CODE::KEY_KEY_M, "M"},
            {EKEY_CODE::KEY_KEY_N, "N"},
            {EKEY_CODE::KEY_KEY_O, "O"},
            {EKEY_CODE::KEY_KEY_P, "P"},
            {EKEY_CODE::KEY_KEY_Q, "Q"},
            {EKEY_CODE::KEY_KEY_R, "R"},
            {EKEY_CODE::KEY_KEY_S, "S"},
            {EKEY_CODE::KEY_KEY_T, "T"},
            {EKEY_CODE::KEY_KEY_U, "U"},
            {EKEY_CODE::KEY_KEY_V, "V"},
            {EKEY_CODE::KEY_KEY_W, "W"},
            {EKEY_CODE::KEY_KEY_X, "X"},
            {EKEY_CODE::KEY_KEY_Y, "Y"},
            {EKEY_CODE::KEY_KEY_Z, "Z"},
            {EKEY_CODE::KEY_KEY_1, "1"},
            {EKEY_CODE::KEY_KEY_2, "2"},
            {EKEY_CODE::KEY_KEY_3, "3"},
            {EKEY_CODE::KEY_KEY_4, "4"},
            {EKEY_CODE::KEY_KEY_5, "5"},
            {EKEY_CODE::KEY_KEY_6, "6"},
            {EKEY_CODE::KEY_KEY_7, "7"},
            {EKEY_CODE::KEY_KEY_8, "8"},
            {EKEY_CODE::KEY_KEY_9, "9"},
            {EKEY_CODE::KEY_SPACE, "Space"},
            {EKEY_CODE::KEY_CONTROL, "Ctrl"},
            {EKEY_CODE::KEY_SHIFT, "Shift"},
            {EKEY_CODE::KEY_SPACE, "Space"},
            {EKEY_CODE::KEY_DOWN, "Arrow Down"},
            {EKEY_CODE::KEY_UP, "Arrow Up"},
            {EKEY_CODE::KEY_RIGHT, "Arrow Right"},
            {EKEY_CODE::KEY_LEFT, "Arrow Left"},
            {EKEY_CODE::KEY_KEY_CODES_COUNT, "Unknown"},
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

        static std::string getEquivalentKey(EKEY_CODE key);
        static std::string getEquivalentButton(int button);

        std::vector<std::shared_ptr<TextComponent>> _textPreset;
        std::vector<std::shared_ptr<ImageComponent>> _imagePreset;
        std::vector<std::shared_ptr<ButtonComponent>> _buttonPreset;

    private:
        KeyboardPresetComponent _keyboardPreset;
        JoystickPresetComponent _joystickPreset;

    public:
        int presetNumber;
    };

}

#endif /* !PRESETCOMPONENT_HPP_ */

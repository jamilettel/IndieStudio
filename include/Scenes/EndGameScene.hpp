/*
** EPITECH PROJECT, 2020
** IndieStudio
** File description:
** EndGameScene
*/

#ifndef ENDGAMESCENE_HPP_
#define ENDGAMESCENE_HPP_

#include "ECS/AScene.hpp"
#include "Systems/Audio.hpp"
#include "Systems/Time.hpp"
#include "Systems/Window.hpp"
#include "Systems/Light.hpp"
#include "Systems/Camera.hpp"
#include "Systems/Image.hpp"
#include "Systems/Button.hpp"
#include "Systems/Cursor.hpp"
#include "Prefabs/GlobalPrefabs.hpp"
#include "Prefabs/EndGamePrefabs.hpp"
#include "Systems/ModelRenderer.hpp"
#include "Systems/Texture.hpp"

namespace is::scenes {

    class EndGameScene : public is::ecs::AScene {
        public:
            EndGameScene();
            ~EndGameScene() override = default;

            EndGameScene(const EndGameScene &) = default;
            EndGameScene &operator=(const EndGameScene &) = default;

            void initSystems() override;
            void initEntities() override;
    };

}

#endif /* !ENDGAMESCENE_HPP_ */

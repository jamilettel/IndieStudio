/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Game
*/

#include "Game.hpp"

std::map<std::string, std::shared_ptr<void *>> is::Game::resources;

#ifndef RESOURCES_PATH
    #define RESOURCES_PATH "./resources/"
#endif

#define RESSOURCE(str) std::string(std::string(RESOURCES_PATH) + std::string(str)).c_str()

bool is::Game::isRunning = true;
is::ecs::Scenes is::Game::currentScene = is::ecs::NOTHING;
is::ecs::Scenes is::Game::_previousScene = is::ecs::NOTHING;
bool is::Game::_destroyScene = true;
bool is::Game::_loadScene = true;
std::pair<bool, is::ecs::Scenes> is::Game::_unloadScene;

void is::Game::addScene(is::ecs::Scenes sceneType, const std::shared_ptr<is::ecs::IScene> &scene)
{
    _scenes[sceneType] = scene;
}

void is::Game::switchScene()
{
    unloadScene();
    if (_destroyScene) {
        _scenes[changeScene]->stop();
        _scenes[changeScene]->onTearDown();
    }
    if (_loadScene) {
        _scenes[currentScene]->awake();
        _scenes[currentScene]->start();
    }
    changeScene = currentScene;
}

void is::Game::launchGame(is::ecs::Scenes startScene)
{
    currentScene = startScene;
    changeScene = startScene;
    _previousScene = startScene;
    _scenes[currentScene]->awake();
    _scenes[currentScene]->start();
    while (isRunning) {
        _scenes[currentScene]->update();
        if (currentScene != changeScene)
            switchScene();
    }
    _scenes[currentScene]->stop();
    _scenes[currentScene]->onTearDown();
}

void is::Game::setActualScene(is::ecs::Scenes scene, bool loadScene, bool destroyScene)
{
    _previousScene = currentScene;
    currentScene = scene;
    _loadScene = loadScene;
    _destroyScene = destroyScene;
}

is::ecs::Scenes is::Game::getPreviousScene()
{
    return _previousScene;
}

is::ecs::Scenes is::Game::getCurrentScene()
{
    return currentScene;
}

void is::Game::setUnloadScene(is::ecs::Scenes scene)
{
    _unloadScene.first = true;
    _unloadScene.second = scene;
}

void is::Game::unloadScene()
{
    if (!_unloadScene.first)
        return;
    _scenes[_unloadScene.second]->stop();
    _scenes[_unloadScene.second]->onTearDown();
    _unloadScene.first = false;
}

void is::Game::addResource(const std::string &path, void *resource)
{
    resources[path] = std::make_shared<void *>(resource);
}

void *is::Game::getResource(const std::string &path)
{
    return (*(resources[path].get()));
}

void is::Game::resourcesInitialization(const std::shared_ptr<is::components::WindowComponent> &window)
{
    is::Game::addResource("ui/splashscreen.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/splashscreen.png")));
    is::Game::addResource("ui/cursor/cursor.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/cursor/cursor.png")));
    is::Game::addResource("ui/cursor/cursor2.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/cursor/cursor2.png")));
    is::Game::addResource("ui/cursor/cursor3.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/cursor/cursor3.png")));
    is::Game::addResource("ui/cursor/cursor4.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/cursor/cursor4.png")));
    is::Game::addResource("ui/Alert/Box.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Alert/Box.png")));
    is::Game::addResource("ui/Alert/OkButton.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Alert/OkButton.png")));
    is::Game::addResource("ui/Alert/OkButtonPressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Alert/OkButtonPressed.png")));
    is::Game::addResource("fonts/fontVolumeSettings/fontVolumeSettings.xml",
        (void *)window->canvas->getFont(RESSOURCE("fonts/fontVolumeSettings/fontVolumeSettings.xml")));

    is::Game::addResource("ui/Controllers/LS_RIGHT.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/LS_RIGHT.png")));
    is::Game::addResource("ui/Controllers/LS_UP.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/LS_UP.png")));
    is::Game::addResource("ui/Controllers/LS_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/LS_BUTTON.png")));
    is::Game::addResource("ui/Controllers/RS_LEFT.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/RS_LEFT.png")));
    is::Game::addResource("ui/Controllers/RS_DOWN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/RS_DOWN.png")));
    is::Game::addResource("ui/Controllers/RS_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/RS_BUTTON.png")));
    is::Game::addResource("ui/Controllers/A_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/A_BUTTON.png")));
    is::Game::addResource("ui/Controllers/B_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/B_BUTTON.png")));
    is::Game::addResource("ui/Controllers/X_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/X_BUTTON.png")));
    is::Game::addResource("ui/Controllers/Y_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Y_BUTTON.png")));
    is::Game::addResource("ui/Controllers/LB.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/LB.png")));
    is::Game::addResource("ui/Controllers/RB.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/RB.png")));
    is::Game::addResource("ui/Controllers/BACK_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/BACK_BUTTON.png")));
    is::Game::addResource("ui/Controllers/START_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/START_BUTTON.png")));
    is::Game::addResource("ui/Controllers/HOME_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/HOME_BUTTON.png")));
    is::Game::addResource("ui/Controllers/RS_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/RS_BUTTON.png")));
    is::Game::addResource("ui/Controllers/LS_BUTTON.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/LS_BUTTON.png")));

    is::Game::addResource("ui/background.jpg",
        (void *)window->driver->getTexture(RESSOURCE("ui/background.jpg")));
    is::Game::addResource("ui/Controllers/Controls_title.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Controls_title.png")));
    is::Game::addResource("ui/Controllers/Return_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Return_BTN.png")));
    is::Game::addResource("ui/Controllers/Return_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Return_BTN_pressed.png")));
    is::Game::addResource("ui/Controllers/Controller.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Controller.png")));
    is::Game::addResource("ui/Controllers/Keyboard.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Keyboard.png")));
    is::Game::addResource("ui/Controllers/Forward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Forward_BTN.png")));
    is::Game::addResource("ui/Controllers/Forward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Forward_BTN_pressed.png")));
    is::Game::addResource("ui/Controllers/Backward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Backward_BTN.png")));
    is::Game::addResource("ui/Controllers/Backward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Backward_BTN_pressed.png")));
    is::Game::addResource("ui/Controllers/Change_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Change_BTN.png")));
    is::Game::addResource("ui/Controllers/Change_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Controllers/Change_BTN_pressed.png")));
    is::Game::addResource("ui/background.jpg",
        (void *)window->driver->getTexture(RESSOURCE("ui/background.jpg")));
    is::Game::addResource("player.b3d",
        (void *)window->scenemgr->getMesh(RESSOURCE("player.b3d")));
    is::Game::addResource("ui/EndGame/Table_01.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Table_01.png")));
    is::Game::addResource("ui/EndGame/continue_button.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/continue_button.png")));
    is::Game::addResource("ui/EndGame/continue_button_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/continue_button_pressed.png")));
    is::Game::addResource("ui/EndGame/Backward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Backward_BTN.png")));
    is::Game::addResource("ui/EndGame/Backward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Backward_BTN_pressed.png")));
    is::Game::addResource("ui/EndGame/Forward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Forward_BTN.png")));
    is::Game::addResource("ui/EndGame/Forward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Forward_BTN_pressed.png")));
    is::Game::addResource("ui/EndGame/Table.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Table.png")));
    is::Game::addResource("fonts/EndGame/endGameFont.xml",
        (void *)window->canvas->getFont(RESSOURCE("fonts/EndGame/endGameFont.xml")));
    is::Game::addResource("cubb.obj",
        (void *)window->scenemgr->getMesh(RESSOURCE("cubb.obj")));
    is::Game::addResource("poteau.obj",
        (void *)window->scenemgr->getMesh(RESSOURCE("poteau.obj")));
    is::Game::addResource("grass.obj",
        (void *)window->scenemgr->getMesh(RESSOURCE("grass.obj")));
    is::Game::addResource("crate.obj",
        (void *)window->scenemgr->getMesh(RESSOURCE("crate.obj")));
    is::Game::addResource("bomb.obj",
        (void *)window->scenemgr->getMesh(RESSOURCE("bomb.obj")));
    is::Game::addResource("powerup.b3d",
        (void *)window->scenemgr->getMesh(RESSOURCE("powerup.b3d")));
    is::Game::addResource("bombup.png",
        (void *)window->driver->getTexture(RESSOURCE("bombup.png")));
    is::Game::addResource("speedup.png",
        (void *)window->driver->getTexture(RESSOURCE("speedup.png")));
    is::Game::addResource("fireup.png",
        (void *)window->driver->getTexture(RESSOURCE("fireup.png")));
    is::Game::addResource("wallpass.png",
        (void *)window->driver->getTexture(RESSOURCE("wallpass.png")));
    is::Game::addResource("ui/Game/Table_02.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Game/Table_02.png")));
    is::Game::addResource("ui/main_menu/logo.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/logo.png")));
    is::Game::addResource("ui/main_menu/button_play.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/button_play.png")));
    is::Game::addResource("ui/main_menu/button_play_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/button_play_pressed.png")));
    is::Game::addResource("ui/Multiplayer/multiplayer_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/multiplayer_BTN.png")));
    is::Game::addResource("ui/Multiplayer/multiplayer_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/multiplayer_BTN_pressed.png")));
    is::Game::addResource("ui/main_menu/button_quit.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/button_quit.png")));
    is::Game::addResource("ui/main_menu/button_quit_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/button_quit_pressed.png")));
    is::Game::addResource("ui/main_menu/Controllers_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/Controllers_BTN.png")));
    is::Game::addResource("ui/main_menu/Controllers_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/Controllers_BTN_pressed.png")));
    is::Game::addResource("ui/main_menu/Settings_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/Settings_BTN.png")));
    is::Game::addResource("ui/main_menu/Settings_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/Settings_BTN_pressed.png")));
    is::Game::addResource("ui/main_menu/Scores_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/Scores_BTN.png")));
    is::Game::addResource("ui/main_menu/Scores_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/Scores_BTN_pressed.png")));
    is::Game::addResource("ui/main_menu/FAQ_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/FAQ_BTN.png")));
    is::Game::addResource("ui/main_menu/FAQ_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/FAQ_BTN_pressed.png")));
    is::Game::addResource("ui/main_menu/Info_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/Info_BTN.png")));
    is::Game::addResource("ui/main_menu/Info_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/main_menu/Info_BTN_pressed.png")));
    is::Game::addResource("ui/Pause/Pause.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Pause.png")));
    is::Game::addResource("ui/Pause/logo.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/logo.png")));
    is::Game::addResource("ui/Pause/Continue_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Continue_BTN.png")));
    is::Game::addResource("ui/Pause/Continue_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Continue_BTN_pressed.png")));
    is::Game::addResource("ui/Pause/Menu_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Menu_BTN.png")));
    is::Game::addResource("ui/Pause/Menu_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Menu_BTN_pressed.png")));
    is::Game::addResource("ui/Pause/button_quit.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/button_quit.png")));
    is::Game::addResource("ui/Pause/button_quit_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/button_quit_pressed.png")));
    is::Game::addResource("ui/Pause/Settings_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Settings_BTN.png")));
    is::Game::addResource("ui/Pause/Settings_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Settings_BTN_pressed.png")));
    is::Game::addResource("ui/Pause/Scores_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Scores_BTN.png")));
    is::Game::addResource("ui/Pause/Scores_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Pause/Scores_BTN_pressed.png")));
    is::Game::addResource("ui/Credits/Information.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Credits/Information.png")));
    is::Game::addResource("ui/Credits/Return_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Credits/Return_BTN.png")));
    is::Game::addResource("ui/Credits/Return_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Credits/Return_BTN_pressed.png")));
    is::Game::addResource("ui/HowToPlay/Header.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/HowToPlay/Header.png")));
    is::Game::addResource("ui/HowToPlay/Return_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/HowToPlay/Return_BTN.png")));
    is::Game::addResource("ui/HowToPlay/Return_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/HowToPlay/Return_BTN_pressed.png")));
    is::Game::addResource("ui/PresetSelection/button_play.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/button_play.png")));
    is::Game::addResource("ui/PresetSelection/button_play_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/button_play_pressed.png")));
    is::Game::addResource("ui/PresetSelection/Settings_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Settings_BTN.png")));
    is::Game::addResource("ui/PresetSelection/Settings_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Settings_BTN_pressed.png")));
    is::Game::addResource("ui/PresetSelection/Return_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Return_BTN.png")));
    is::Game::addResource("ui/PresetSelection/Return_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Return_BTN_pressed.png")));
    is::Game::addResource("ui/PresetSelection/Box.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Box.png")));
    is::Game::addResource("ui/PresetSelection/AI.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/AI.png")));
    is::Game::addResource("ui/PresetSelection/Activate_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Activate_BTN.png")));
    is::Game::addResource("ui/PresetSelection/Activate_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Activate_BTN_pressed.png")));
    is::Game::addResource("ui/PresetSelection/Close_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Close_BTN.png")));
    is::Game::addResource("ui/PresetSelection/Close_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Close_BTN_pressed.png")));
    is::Game::addResource("ui/PresetSelection/Backward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Backward_BTN.png")));
    is::Game::addResource("ui/PresetSelection/Backward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Backward_BTN_pressed.png")));
    is::Game::addResource("ui/PresetSelection/Forward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Forward_BTN.png")));
    is::Game::addResource("ui/PresetSelection/Forward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/PresetSelection/Forward_BTN_pressed.png")));
    is::Game::addResource("ui/RuleSettings/Return_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Return_BTN.png")));
    is::Game::addResource("ui/RuleSettings/Return_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Return_BTN_pressed.png")));
    is::Game::addResource("ui/RuleSettings/Forward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Forward_BTN.png")));
    is::Game::addResource("ui/RuleSettings/Forward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")));
    is::Game::addResource("ui/RuleSettings/Backward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Backward_BTN.png")));
    is::Game::addResource("ui/RuleSettings/Backward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Backward_BTN_pressed.png")));
    is::Game::addResource("ui/RuleSettings/Backward_BTN.png",
                (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Backward_BTN.png")));
    is::Game::addResource("ui/RuleSettings/Table.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Table.png")));
    is::Game::addResource("ui/RuleSettings/Upward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Upward_BTN.png")));
    is::Game::addResource("ui/RuleSettings/Upward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Upward_BTN_pressed.png")));
    is::Game::addResource("ui/RuleSettings/Downward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Downward_BTN.png")));
    is::Game::addResource("ui/RuleSettings/Downward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Downward_BTN_pressed.png")));
    is::Game::addResource("ui/RuleSettings/Dot_01.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Dot_01.png")));
    is::Game::addResource("ui/RuleSettings/Table_01.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Table_01.png")));
    is::Game::addResource("ui/RuleSettings/Forward_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Forward_BTN.png")));
    is::Game::addResource("ui/RuleSettings/Forward_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Forward_BTN_pressed.png")));
    is::Game::addResource("ui/RuleSettings/Dot_01.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Dot_01.png")));
    is::Game::addResource("ui/RuleSettings/Box.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/Box.png")));
    is::Game::addResource("ui/RuleSettings/disable.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/disable.png")));
    is::Game::addResource("ui/RuleSettings/accelerator.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/accelerator.png")));
    is::Game::addResource("ui/RuleSettings/bomb.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/bomb.png")));
    is::Game::addResource("ui/RuleSettings/explosion_expander.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/explosion_expander.png")));
    is::Game::addResource("ui/RuleSettings/wall_pass.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/wall_pass.png")));
    is::Game::addResource("ui/RuleSettings/OkButton.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/OkButton.png")));
    is::Game::addResource("ui/RuleSettings/OkButtonPressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/RuleSettings/OkButtonPressed.png")));
    is::Game::addResource("ui/settings/Header.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Header.png")));
    is::Game::addResource("ui/settings/Return_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Return_BTN.png")));
    is::Game::addResource("ui/settings/Return_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Return_BTN_pressed.png")));
    is::Game::addResource("ui/settings/Window.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Window.png")));
    is::Game::addResource("ui/settings/Music.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Music.png")));
    is::Game::addResource("ui/settings/Sound_no_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound_no_BTN.png")));
    is::Game::addResource("ui/settings/Sound_no_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound_no_BTN_pressed.png")));
    is::Game::addResource("ui/settings/Sound_high_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound_high_BTN.png")));
    is::Game::addResource("ui/settings/Sound_high_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound_high_BTN_pressed.png")));
    is::Game::addResource("ui/settings/Sound_low_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound_low_BTN.png")));
    is::Game::addResource("ui/settings/Sound_low_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound_low_BTN_pressed.png")));
    is::Game::addResource("ui/settings/Sound.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound.png")));
    is::Game::addResource("ui/settings/Sound_no_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound_no_BTN.png")));
    is::Game::addResource("ui/settings/Sound_no_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/settings/Sound_no_BTN_pressed.png")));
    is::Game::addResource("ui/Multiplayer/down_btn.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/down_btn.png")));
    is::Game::addResource("ui/Multiplayer/down_btn_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/down_btn_pressed.png")));
    is::Game::addResource("ui/Multiplayer/up_btn.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/up_btn.png")));
    is::Game::addResource("ui/Multiplayer/up_btn_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/up_btn_pressed.png")));
    is::Game::addResource("ui/Multiplayer/number_frame.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/number_frame.png")));
    is::Game::addResource("ui/Multiplayer/Return_BTN_pressed.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/Return_BTN_pressed.png")));
    is::Game::addResource("ui/Multiplayer/Return_BTN.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/Multiplayer/Return_BTN.png")));
    is::Game::addResource("player_white.png",
        (void *)window->driver->getTexture(RESSOURCE("player_white.png")));
    is::Game::addResource("player_black.png",
        (void *)window->driver->getTexture(RESSOURCE("player_black.png")));
    is::Game::addResource("player_blue.png",
        (void *)window->driver->getTexture(RESSOURCE("player_blue.png")));
    is::Game::addResource("player_red.png",
        (void *)window->driver->getTexture(RESSOURCE("player_red.png")));
    is::Game::addResource("ui/EndGame/Star_01.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Star_01.png")));
    is::Game::addResource("ui/EndGame/Star_02.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Star_02.png")));
    is::Game::addResource("ui/EndGame/Star_03.png",
        (void *)window->driver->getTexture(RESSOURCE("ui/EndGame/Star_03.png")));
    is::Game::addResource("fire.bmp",
        (void *)window->driver->getTexture(RESSOURCE("fire.bmp")));
}

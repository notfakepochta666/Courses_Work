#pragma once
#include <SFML/Graphics.hpp>

#include "../Audio/AudioManager.h"
#include "../Scenes/MenuScene.h"
#include "../Scenes/SettingsScene.h"
#include "../Scenes/GameScene.h"
#include "../Cutscenes/IntroCutscene.h"
#include "../Entity/Player.h"
#include "../Level/Level.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Clock clock;
    float dt = 0.f;

    AudioManager audio;
    MenuScene menu;
    SettingsScene settings;
    GameScene game;
    IntroCutscene intro;
    Player player;
    Level level;

    int state = 0;        // MENU
    int returnState = 0;  // куда возвращаемся из settings

    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};
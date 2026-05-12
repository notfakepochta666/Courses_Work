#pragma once
#include <SFML/Graphics.hpp>

class GameScene
{
private:
    sf::Texture settingsTexture;
    sf::Sprite settingsBtn;

    bool isSettingsHovered = false;

public:
    GameScene();

    void handleEvent(sf::Event& event, sf::RenderWindow& window, int& state);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
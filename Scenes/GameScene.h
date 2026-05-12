#pragma once
#include <SFML/Graphics.hpp>

class GameScene
{
private:
    sf::Texture settingsTexture;
    sf::Sprite settingsBtn;

public:
    GameScene();

    void handleEvent(sf::Event& event, sf::RenderWindow& window, int& state);
    void update(float dt);
    void draw(sf::RenderWindow& window);
};
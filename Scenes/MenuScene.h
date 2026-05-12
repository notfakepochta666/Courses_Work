#pragma once
#include <SFML/Graphics.hpp>

class MenuScene
{
private:
    sf::Texture bgTexture;
    sf::Sprite background;

    sf::FloatRect playBtn;
    sf::FloatRect settingsBtn;
    sf::FloatRect exitBtn;

public:
    MenuScene();

    void handleEvent(sf::Event& event, sf::RenderWindow& window, int& state);
    void draw(sf::RenderWindow& window);
};
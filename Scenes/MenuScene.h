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

    bool isPlayHovered = false;
    bool isSettingsHovered = false;
    bool isExitHovered = false;

public:
    MenuScene();

    void handleEvent(sf::Event& event, sf::RenderWindow& window, int& state);
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
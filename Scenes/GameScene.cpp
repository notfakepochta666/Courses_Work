#include "GameScene.h"

GameScene::GameScene()
{
    settingsTexture.loadFromFile("assets/images/setting-sign.png");
    settingsBtn.setTexture(settingsTexture);
    settingsBtn.setPosition(35, 35);
    settingsBtn.setScale(0.035f, 0.035f);
}

void GameScene::handleEvent(sf::Event& event, sf::RenderWindow& window, int& state)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));

        if (settingsBtn.getGlobalBounds().contains(mouse))
            state = 1;
    }
}

void GameScene::update(float dt)
{
}

void GameScene::draw(sf::RenderWindow& window)
{
    window.draw(settingsBtn);
}
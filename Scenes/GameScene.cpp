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

void GameScene::update(sf::RenderWindow& window)
{
    sf::Vector2f mouse = window.mapPixelToCoords(
        sf::Mouse::getPosition(window));

    isSettingsHovered = settingsBtn.getGlobalBounds().contains(mouse);
}

void GameScene::draw(sf::RenderWindow& window)
{
    // ===== ондяберйю =====
    if (isSettingsHovered)
    {
        sf::RectangleShape highlight(sf::Vector2f(
            settingsBtn.getGlobalBounds().width,
            settingsBtn.getGlobalBounds().height));
        highlight.setPosition(
            settingsBtn.getGlobalBounds().left,
            settingsBtn.getGlobalBounds().top);
        highlight.setFillColor(sf::Color(255, 255, 255, 100));
        window.draw(highlight);
    }

    window.draw(settingsBtn);
}
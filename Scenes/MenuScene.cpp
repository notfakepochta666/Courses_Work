#include "MenuScene.h"
#include <iostream>

MenuScene::MenuScene()
{
    bgTexture.loadFromFile("assets/images/menu.png");
    background.setTexture(bgTexture);

    sf::Vector2u textureSize = bgTexture.getSize();
    sf::Vector2u windowSize(1280, 720);

    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    background.setScale(scaleX, scaleY);

    playBtn = sf::FloatRect(400, 335, 475, 85);
    settingsBtn = sf::FloatRect(400, 435, 475, 85);
    exitBtn = sf::FloatRect(400, 535, 475, 85);
}

void MenuScene::handleEvent(sf::Event& event, sf::RenderWindow& window, int& state)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));

        if (playBtn.contains(mouse))
            state = 3;

        if (settingsBtn.contains(mouse))
            state = 1;

        if (exitBtn.contains(mouse))
            window.close();
    }
}

void MenuScene::update(sf::RenderWindow& window)
{
    sf::Vector2f mouse = window.mapPixelToCoords(
        sf::Mouse::getPosition(window));

    isPlayHovered = playBtn.contains(mouse);
    isSettingsHovered = settingsBtn.contains(mouse);
    isExitHovered = exitBtn.contains(mouse);
}

void MenuScene::draw(sf::RenderWindow& window)
{
    window.draw(background);

    // ===== ПОДСВЕТКА КНОПОК =====
    if (isPlayHovered)
    {
        sf::RectangleShape highlight(sf::Vector2f(playBtn.width, playBtn.height));
        highlight.setPosition(playBtn.left, playBtn.top);
        highlight.setFillColor(sf::Color(255, 255, 255, 100));
        window.draw(highlight);
    }

    if (isSettingsHovered)
    {
        sf::RectangleShape highlight(sf::Vector2f(settingsBtn.width, settingsBtn.height));
        highlight.setPosition(settingsBtn.left, settingsBtn.top);
        highlight.setFillColor(sf::Color(255, 255, 255, 100));
        window.draw(highlight);
    }

    if (isExitHovered)
    {
        sf::RectangleShape highlight(sf::Vector2f(exitBtn.width, exitBtn.height));
        highlight.setPosition(exitBtn.left, exitBtn.top);
        highlight.setFillColor(sf::Color(255, 255, 255, 100));
        window.draw(highlight);
    }
}
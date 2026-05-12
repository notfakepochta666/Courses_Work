#include "Level.h"

void Level::load()
{
    backgrounds.resize(2);

    backgrounds[0].loadFromFile("assets/images/bg1-1.png");
    backgrounds[1].loadFromFile("assets/images/bg1-2.png");

    background.setTexture(backgrounds[0]);

    sf::Vector2u size = backgrounds[0].getSize();

    float scaleX = worldWidth / size.x;
    float scaleY = 720.f / size.y;

    background.setScale(scaleX, scaleY);

    // 🧱 земля
    platforms.emplace_back(0.f, 650.f, 2000.f, 70.f);

    // платформы
    platforms.emplace_back(250.f, 520.f, 180.f, 25.f);
    platforms.emplace_back(550.f, 430.f, 180.f, 25.f);
    platforms.emplace_back(850.f, 350.f, 180.f, 25.f);
}

void Level::update(float playerX)
{
    if (playerX > worldWidth && currentLevel == 0)
    {
        currentLevel = 1;
        background.setTexture(backgrounds[1]);
        switched = true;
    }
}

void Level::draw(sf::RenderWindow& window)
{
    window.draw(background);

    for (auto& p : platforms)
        p.draw(window);
}
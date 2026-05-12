#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity/Platform.h"

class Level
{
private:
    std::vector<sf::Texture> backgrounds;
    sf::Sprite background;

    std::vector<Platform> platforms;

    int currentLevel = 0;
    float worldWidth = 1280.f;
    bool switched = false;

public:
    void load();
    void update(float playerX);
    void draw(sf::RenderWindow& window);

    const std::vector<Platform>& getPlatforms() const { return platforms; }

    int getLevel() const { return currentLevel; }
    bool isSwitched() const { return switched; }
    void resetSwitch() { switched = false; }
};
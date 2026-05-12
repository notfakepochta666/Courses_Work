#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity/Platform.h"

class Player
{
private:
    sf::Sprite sprite;

    std::vector<sf::Texture> walk;
    std::vector<sf::Texture> jump;

    float speed = 220.f;

    float posX = 100.f;
    float posY = 600.f;

    float velocityY = 0.f;
    float gravity = 950.f;
    float jumpForce = -450.f;

    bool inAir = false;
    bool right = true;
    bool moving = false;
    bool jumpPressed = false;

    float animTimer = 0.f;
    int frame = 0;
    int walkDirection = 1;

public:
    void load();
    void update(float dt, const std::vector<Platform>& platforms);
    void draw(sf::RenderWindow& window);

    float getX() const { return posX; }

    sf::FloatRect getBounds() const;

    void resetPosition()
    {
        posX = 100.f;
        posY = 600.f;
        velocityY = 0.f;
        inAir = false;
    }
};
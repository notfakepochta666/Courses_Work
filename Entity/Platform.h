#pragma once
#include <SFML/Graphics.hpp>

class Platform
{
private:
    sf::RectangleShape shape;

public:
    Platform() = default;

    Platform(float x, float y, float w, float h)
    {
        shape.setPosition(x, y);
        shape.setSize({ w, h });
        shape.setFillColor(sf::Color(20, 20, 20));
    }

    sf::FloatRect getBounds() const
    {
        return shape.getGlobalBounds();
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }
};
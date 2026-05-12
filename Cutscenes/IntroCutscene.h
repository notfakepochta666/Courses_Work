#pragma once
#include <SFML/Graphics.hpp>

class IntroCutscene
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

    sf::RectangleShape skipBtn;

    sf::Font font;
    sf::Text skipText;

    float y = 0.f;
    float speed = 110.f;

    bool finished = false;
    bool started = false;
    sf::Clock timer;

    bool isSkipHovered = false;

public:
    void load();
    void reset();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);

    bool isFinished();
};
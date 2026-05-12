#include "IntroCutscene.h"
#include <iostream>

void IntroCutscene::load()
{
    texture.loadFromFile("assets/cutscenes/begin1.png");
    sprite.setTexture(texture);
    sprite.setScale(0.70f, 0.70f);

    // ===== КНОПКА SKIP =====
    skipBtn.setSize(sf::Vector2f(160.f, 50.f));
    skipBtn.setFillColor(sf::Color(0, 0, 0, 180)); // чуть прозрачнее

    // ===== ШРИФТ =====
    if (!font.loadFromFile("assets/fonts/PressStart2P-Regular.ttf"))
    {
        std::cout << "FONT NOT LOADED\n";
    }

    skipText.setFont(font);
    skipText.setString("SKIP");
    skipText.setCharacterSize(18);
    skipText.setFillColor(sf::Color::White);

    reset();
}

void IntroCutscene::reset()
{
    y = 0.f;
    sprite.setPosition(0.f, y);

    finished = false;
    started = false;
    timer.restart();

    // кнопка справа снизу
    skipBtn.setPosition(1100.f, 650.f);

    // текст по центру кнопки
    sf::FloatRect bounds = skipBtn.getGlobalBounds();

    skipText.setPosition(
        bounds.left + 40.f,
        bounds.top + 15.f
    );
}

void IntroCutscene::update(float dt)
{
    if (finished) return;

    // пауза перед началом
    if (!started)
    {
        if (timer.getElapsedTime().asSeconds() < 3.f)
            return;

        started = true;
    }

    // движение катсцены
    y -= speed * dt;
    sprite.setPosition(0.f, y);

    float h = texture.getSize().y * sprite.getScale().y;

    if (y + h < 0)
        finished = true;
}

void IntroCutscene::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);

        // ⭐ СКИП ТОЛЬКО ЕСЛИ КЛИК ПО КНОПКЕ
        if (skipBtn.getGlobalBounds().contains(mouse))
            finished = true;
    }
}

void IntroCutscene::draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    window.draw(skipBtn);
    window.draw(skipText);
}

bool IntroCutscene::isFinished()
{
    return finished;
}
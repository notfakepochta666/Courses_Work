#include "Player.h"

void Player::load()
{
    walk.resize(4);
    jump.resize(6);

    walk[0].loadFromFile("assets/images/player/walk1.png");
    walk[1].loadFromFile("assets/images/player/walk2.png");
    walk[2].loadFromFile("assets/images/player/walk3.png");
    walk[3].loadFromFile("assets/images/player/walk4.png");

    jump[0].loadFromFile("assets/images/player/jump1.png");
    jump[1].loadFromFile("assets/images/player/jump2.png");
    jump[2].loadFromFile("assets/images/player/jump3.png");
    jump[3].loadFromFile("assets/images/player/jump4.png");
    jump[4].loadFromFile("assets/images/player/jump5.png");
    jump[5].loadFromFile("assets/images/player/jump6.png");

    sprite.setTexture(walk[0]);

    // ВАЖНО:
    // origin снизу по центру
    sf::Vector2u size = walk[0].getSize();
    sprite.setOrigin(size.x / 2.f, size.y);

    sprite.setScale(3.f, 3.f);
    sprite.setPosition(posX, posY);
}

void Player::update(float dt, const std::vector<Platform>& platforms)
{
    moving = false;

    // =========================
    // ДВИЖЕНИЕ
    // =========================

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        posX += speed * dt;
        moving = true;
        right = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        posX -= speed * dt;
        moving = true;
        right = false;
    }

    // =========================
    // ПРЫЖОК
    // =========================

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !inAir)
    {
        velocityY = jumpForce;
        inAir = true;
    }

    // =========================
    // ГРАВИТАЦИЯ
    // =========================

    velocityY += gravity * dt;
    posY += velocityY * dt;

    // =========================
    // ОБНОВЛЯЕМ ПОЗИЦИЮ СПРАЙТА
    // ДО КОЛЛИЗИИ
    // =========================

    sprite.setPosition(posX, posY);

    // =========================
    // КОЛЛИЗИЯ
    // =========================

    inAir = true;

    sf::FloatRect playerBounds = sprite.getGlobalBounds();

    for (const auto& p : platforms)
    {
        sf::FloatRect plat = p.getBounds();

        if (playerBounds.intersects(plat))
        {
            // приземление только сверху
            if (velocityY > 0)
            {
                posY = plat.top;

                velocityY = 0.f;
                inAir = false;

                sprite.setPosition(posX, posY);

                playerBounds = sprite.getGlobalBounds();
            }
        }
    }

    // =========================
    // АНИМАЦИИ
    // =========================

    if (moving && !inAir)
    {
        animTimer += dt;

        if (animTimer >= 0.15f)
        {
            animTimer = 0.f;
            frame++;

            if (frame >= walk.size())
                frame = 0;
        }

        sprite.setTexture(walk[frame]);
    }
    else if (inAir)
    {
        sprite.setTexture(jump[0]);
    }
    else
    {
        sprite.setTexture(walk[0]);
    }

    // =========================
    // ОТРАЖЕНИЕ
    // =========================

    if (right)
        sprite.setScale(3.f, 3.f);
    else
        sprite.setScale(-3.f, 3.f);

    sprite.setPosition(posX, posY);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}
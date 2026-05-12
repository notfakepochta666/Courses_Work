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
        sf::Keyboard::isKeyPressed(sf::Keyboard::W)) && !inAir && !jumpPressed)
    {
        velocityY = jumpForce;
        inAir = true;
        jumpPressed = true;
    }

    // Отпустили кнопку - можно прыгнуть снова
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        jumpPressed = false;
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
    // КОЛЛИЗИЯ - УЛУЧШЕННАЯ СИСТЕМА
    // =========================

    inAir = true;

    sf::FloatRect playerBounds = sprite.getGlobalBounds();

    // Для правильного позиционирования нужна половина высоты спрайта
    // с учетом масштаба (так как origin внизу по центру)
    sf::Vector2u playerSize = walk[frame].getSize();
    float playerHeight = playerSize.y * sprite.getScale().y;

    for (const auto& p : platforms)
    {
        sf::FloatRect platBounds = p.getBounds();

        if (playerBounds.intersects(platBounds))
        {
            // ✅ ПРИЗЕМЛЕНИЕ СВЕРХУ: котик падал вниз на платформу
            // Проверяем, что предыдущая позиция была выше платформы
            if (velocityY > 0)
            {
                // Проверяем, что котик приходит именно сверху
                // (предыдущая Y была выше платформы)
                float prevY = posY - velocityY * dt;
                if (prevY <= platBounds.top + 5.f)  // небольшой допуск для корректности
                {
                    // 🎯 ПРАВИЛЬНАЯ ПОЗИЦИЯ: котик стоит ровно на платформе
                    // Поскольку origin внизу спрайта, то posY = верх платформы
                    posY = platBounds.top;

                    velocityY = 0.f;
                    inAir = false;

                    sprite.setPosition(posX, posY);
                    playerBounds = sprite.getGlobalBounds();
                }
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
            frame += walkDirection;

            // Пинг-понг анимация ходьбы
            if (frame >= (int)walk.size() - 1)
                walkDirection = -1;
            else if (frame <= 0)
                walkDirection = 1;
        }

        sprite.setTexture(walk[frame]);
    }
    else if (inAir)
    {
        // Анимация прыжка синхронизирована с физикой
        if (velocityY < -100.f)
            sprite.setTexture(jump[0]);  // взлёт вверх активный
        else if (velocityY < -50.f)
            sprite.setTexture(jump[1]);  // взлёт замедляется
        else if (velocityY < 50.f)
            sprite.setTexture(jump[3]);  // ⭐ пик прыжка (нулевая скорость)
        else if (velocityY < 200.f)
            sprite.setTexture(jump[4]);  // начало падения
        else
            sprite.setTexture(jump[5]);  // быстрое падение
    }
    else
    {
        sprite.setTexture(walk[0]);
        frame = 0;
        walkDirection = 1;
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

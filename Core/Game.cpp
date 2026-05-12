#include "Game.h"

Game::Game()
    : window(sf::VideoMode(1280, 720), "Game")
{
    audio.init();
    audio.playMenuMusic();

    settings.setAudio(&audio);
    intro.load();

    // ЗАГРУЖАЕМ КОТИКА
    player.load();
    level.load();
}

void Game::run()
{
    while (window.isOpen())
    {
        dt = clock.restart().asSeconds();

        audio.update();

        processEvents();
        update();
        render();
    }
}

void Game::update()
{
    // CUTSCENE
    if (state == 3)
    {
        intro.update(dt);

        if (intro.isFinished())
            state = 2;
    }

    // GAME
    if (state == 2)
    {
        game.update(window);
        player.update(dt, level.getPlatforms());

        level.update(player.getX());

        if (level.isSwitched())
        {
            player.resetPosition();

            level.resetSwitch();
        }
    }

    // MENU
    if (state == 0)
    {
        menu.update(window);
    }
}

void Game::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
            audio.playClick();

        // ================= MENU =================
        if (state == 0)
        {
            int newState = state;
            menu.handleEvent(event, window, newState);

            if (newState == 1) // settings из меню
            {
                returnState = 0;
                state = 1;
            }
            else if (newState == 3) // start game
            {
                intro.reset();
                state = 3;
            }
        }

        // ================= SETTINGS =================
        else if (state == 1)
        {
            int newState = state;
            settings.handleEvent(event, window, newState);

            if (newState == 0)
                state = returnState; // возвращаемся туда откуда пришли
        }

        // ================= GAME =================
        else if (state == 2)
        {
            int newState = state;
            game.handleEvent(event, window, newState);

            if (newState == 1) // открыть настройки из игры
            {
                returnState = 2;
                state = 1;
            }
        }

        // ================= CUTSCENE =================
        else if (state == 3)
        {
            intro.handleEvent(event, window);
        }
    }
}

void Game::render()
{
    // красивый фон только в игре
    if (state == 2)
        window.clear(sf::Color(100, 150, 255));
    else
        window.clear();

    if (state == 0)
        menu.draw(window);

    else if (state == 1)
        settings.draw(window);

    else if (state == 2)
    {
        game.draw(window);

        level.draw(window);   // ⭐ фон

        player.draw(window);  // кот поверх
    }

    else if (state == 3)
        intro.draw(window);

    window.display();
}
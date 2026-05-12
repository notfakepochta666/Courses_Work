#include "SettingsScene.h"
#include "../Audio/AudioManager.h"

SettingsScene::SettingsScene()
{
    bgTexture.loadFromFile("assets/images/settings.png");
    background.setTexture(bgTexture);

    sf::Vector2u textureSize = bgTexture.getSize();
    sf::Vector2u windowSize(1280, 720);

    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    background.setScale(scaleX, scaleY);

    musicBtn.setRadius(25);
    musicBtn.setPosition(600, 270);

    sfxBtn.setRadius(25);
    sfxBtn.setPosition(600, 395);

    // кнопка назад
    backTexture.loadFromFile("assets/images/back.png");
    backBtn.setTexture(backTexture);
    backBtn.setPosition(65, 55);

    sf::Vector2u size = backTexture.getSize();
    backBtn.setOrigin(size.x / 2.f, size.y / 2.f);

    // ⭐ зеркалим по X (делаем стрелку влево)
    backBtn.setScale(-1.f, 1.f);

}

void SettingsScene::setAudio(AudioManager* a)
{
    audio = a;
}

void SettingsScene::handleEvent(sf::Event& event, sf::RenderWindow& window, int& state)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mouse = window.mapPixelToCoords(
            sf::Mouse::getPosition(window));

        if (backBtn.getGlobalBounds().contains(mouse))
            state = 0;

        if (musicBtn.getGlobalBounds().contains(mouse))
        {
            musicOn = !musicOn;

            if (audio)
                audio->setMusicEnabled(musicOn);
        }
        if (sfxBtn.getGlobalBounds().contains(mouse))
            sfxOn = !sfxOn;

        if (audio)
            audio->setSfxEnabled(sfxOn);
    }
}

void SettingsScene::draw(sf::RenderWindow& window)
{
    window.draw(background);

    musicBtn.setFillColor(musicOn ? sf::Color(144, 238, 144) : sf::Color::Black);
    sfxBtn.setFillColor(sfxOn ? sf::Color(144, 238, 144) : sf::Color::Black);

    window.draw(musicBtn);
    window.draw(sfxBtn);
    window.draw(backBtn);
}
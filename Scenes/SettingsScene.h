#pragma once
#include <SFML/Graphics.hpp>

class AudioManager;

class SettingsScene
{
private:
    sf::Texture bgTexture;
    sf::Sprite background;

    sf::CircleShape musicBtn;
    sf::CircleShape sfxBtn;
    sf::Texture backTexture;
    sf::Sprite backBtn;

    bool musicOn = true;
    bool sfxOn = true;

    AudioManager* audio = nullptr;

public:
    SettingsScene();

    void setAudio(AudioManager* a);

    void handleEvent(sf::Event& event, sf::RenderWindow& window, int& state);
    void draw(sf::RenderWindow& window);
};
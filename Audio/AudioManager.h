#pragma once
#include <SFML/Audio.hpp>

class AudioManager
{
private:
    sf::Music menuMusic;

    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    bool musicEnabled = true;
    bool sfxEnabled = true;

public:
    void init();

    // музыка
    void playMenuMusic();
    void stopMusic();

    void setMusicEnabled(bool enabled);
    void setSfxEnabled(bool enabled);

    bool isSfxEnabled();

    // обновление состояния (⭐ ВАЖНО)
    void update();

    // звуки
    void playClick();
};
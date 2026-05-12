#include "AudioManager.h"

void AudioManager::init()
{
    menuMusic.openFromFile("assets/audio/music/menu.ogg");
    menuMusic.setLoop(true);
    menuMusic.setVolume(50);

    clickBuffer.loadFromFile("assets/audio/sfx/click.wav");
    clickSound.setBuffer(clickBuffer);
}

void AudioManager::playMenuMusic()
{
    if (musicEnabled && menuMusic.getStatus() != sf::Music::Playing)
        menuMusic.play();
}

void AudioManager::stopMusic()
{
    menuMusic.stop();
}

void AudioManager::setMusicEnabled(bool enabled)
{
    musicEnabled = enabled;
}

void AudioManager::setSfxEnabled(bool enabled)
{
    sfxEnabled = enabled;
}

bool AudioManager::isSfxEnabled()
{
    return sfxEnabled;
}

void AudioManager::update()
{
    // ⭐ ЕДИНСТВЕННОЕ МЕСТО КОНТРОЛЯ МУЗЫКИ

    if (!musicEnabled)
    {
        if (menuMusic.getStatus() == sf::Music::Playing)
            menuMusic.stop();
    }
    else
    {
        if (menuMusic.getStatus() != sf::Music::Playing)
            menuMusic.play();
    }
}

void AudioManager::playClick()
{
    if (!sfxEnabled)
        return;

    clickSound.play();
}
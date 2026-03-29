#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <memory>
#include "Button.h"

class MainMenu
{
private:
    sf::Font font;

    std::unique_ptr<Button> newGame;
    std::unique_ptr<Button> loadSave;

    sf::Texture backgroundTexture;
    sf::Sprite background;

public:
    MainMenu();

    void handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
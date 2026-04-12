#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <memory>
#include "Button.h"

class MainMenu
{
public:
    enum class State { Menu, Playing, Finished };

private:
    State state = State::Menu;

    sf::Font font;

    std::unique_ptr<Button> newGame;
    std::unique_ptr<Button> loadSave;

    // Room progression
    int currentRoom = 0;
    const int totalRooms = 10;

    // Visuals for the playing state
    sf::RectangleShape doorRect;   // vertical gray rectangle in middle

    // sf::Text doesn't have a default ctor in this SFML; construct after font loads
    std::unique_ptr<sf::Text> congratsText;

public:
    MainMenu();

    void handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
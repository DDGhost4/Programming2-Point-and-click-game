#include "MainMenu.h"
#include <iostream>
#include <filesystem>

MainMenu::MainMenu()
    : background(backgroundTexture) // initialize sprite with texture reference
{
    namespace fs = std::filesystem;

    // Print current working directory so you can verify where the exe looks for files
    std::cout << "Current working directory: " << fs::current_path() << '\n';

    // Load font (SFML 3 uses openFromFile)
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Font failed to load from 'arial.ttf'\n";
    }

    // Diagnostic: check file exists before attempting to load
    if (!fs::exists("cave.png"))
    {
        std::cout << "Warning: 'cave.png' not found in working directory\n";
    }

    if (!backgroundTexture.loadFromFile("cave.png"))
    {
        std::cout << "Background failed to load from 'cave.png'\n";
    }
    else
    {
        background.setTexture(backgroundTexture, true);

        auto size = backgroundTexture.getSize();
        if (size.x == 0 || size.y == 0)
        {
            std::cout << "Background texture size is zero — skipping scale\n";
        }
        else
        {
            background.setScale({
                800.f / static_cast<float>(size.x),
                600.f / static_cast<float>(size.y)
            });
        }
    }

    // Create buttons after font has been loaded
    newGame = std::make_unique<Button>(font, "New Game", sf::Vector2f{250.f, 60.f}, sf::Vector2f{275.f, 220.f});
    loadSave = std::make_unique<Button>(font, "Load Save", sf::Vector2f{250.f, 60.f}, sf::Vector2f{275.f, 320.f});
}

void MainMenu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window)
{
    if (!event) return;

    if (event->is<sf::Event::MouseButtonPressed>())
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (newGame && newGame->isClicked(mousePos))
            std::cout << "New Game clicked\n";

        if (loadSave && loadSave->isClicked(mousePos))
            std::cout << "Load Save clicked\n";
    }
    else if (event->is<sf::Event::Closed>())
    {
        window.close();
    }
}

void MainMenu::draw(sf::RenderWindow& window)
{
    window.draw(background);
    if (newGame) newGame->draw(window);
    if (loadSave) loadSave->draw(window);
}
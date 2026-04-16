#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu()
{
    // Load font (SFML 3 uses openFromFile)
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Font failed to load from 'arial.ttf'\n";
    }

    // Create menu buttons (positions chosen to fit 800x600)
    newGame = std::make_unique<Button>(font, "New Game", sf::Vector2f{250.f, 60.f}, sf::Vector2f{275.f, 220.f});
    loadSave = std::make_unique<Button>(font, "Load Game", sf::Vector2f{250.f, 60.f}, sf::Vector2f{275.f, 320.f});

    // Setup vertical gray rectangle (door) centered in the window (800x600)
    sf::Vector2f doorSize{100.f, 400.f}; // vertical rectangle
    doorRect.setSize(doorSize);
    doorRect.setFillColor(sf::Color(150, 150, 150)); // gray
    // center it: position = (windowWidth - doorWidth)/2, (windowHeight - doorHeight)/2
    doorRect.setPosition({ (800.f - doorSize.x) / 2.f, (600.f - doorSize.y) / 2.f });

    // Congrats text (constructed after font loaded)
    congratsText = std::make_unique<sf::Text>(font, sf::String("Congrats! You beat the dungeon"), 32);
    congratsText->setFillColor(sf::Color::White);
    // Place roughly centered (simple placement)
    congratsText->setPosition({ 120.f, 280.f });
}

void MainMenu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window)
{
    if (!event) return;

    // Map mouse pixel to world coords
    if (event->is<sf::Event::MouseButtonPressed>())
    {
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

        if (state == State::Menu)
        {
            if (newGame && newGame->isClicked(mousePos))
            {
                // start new game
                currentRoom = 1;
                state = State::Playing;
                std::cout << "New Game started\n";
            }
            else if (loadSave && loadSave->isClicked(mousePos))
            {
                // load game (placeholder)
                std::cout << "Load Game requested (not implemented)\n";
            }
        }
        else if (state == State::Playing)
        {
            // Clicking the middle rectangle advances to the next room
            if (doorRect.getGlobalBounds().contains(mousePos))
            {
                if (currentRoom < totalRooms)
                {
                    ++currentRoom;
                    std::cout << "Moved to room " << currentRoom << '\n';
                }

                // If we've reached the final room number, move to Finished
                if (currentRoom >= totalRooms)
                {
                    state = State::Finished;
                    std::cout << "Reached final room, finished dungeon\n";
                }
            }
        }
        else if (state == State::Finished)
        {
            // no-op for now
        }
    }
    else if (event->is<sf::Event::Closed>())
    {
        window.close();
    }
}

void MainMenu::draw(sf::RenderWindow& window)
{
    if (state == State::Menu)
    {
        // Draw the menu buttons
        if (newGame) newGame->draw(window);
        if (loadSave) loadSave->draw(window);
    }
    else if (state == State::Playing)
    {
        // Background is cleared by main loop to black; draw the gray vertical rectangle
        window.draw(doorRect);
    }
    else if (state == State::Finished)
    {
        // Draw congratulations text
        if (congratsText) window.draw(*congratsText);
    }
}
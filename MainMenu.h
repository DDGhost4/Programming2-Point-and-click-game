#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
#include <memory>
#include <vector>
#include <string>

#include "Button.h"
#include "Actor.h"
#include "Items.h"
#include "Player Save.h"
#include <filesystem>

struct GameRoom
{
    int id{};
    std::unique_ptr<Enemy> enemy; // optional enemy in the room
    // placeholder for future content
};

class MainMenu
{
public:
    enum class State { Menu, Playing, GameOver, Finished };


private:
    State state = State::Menu;

    sf::Font font;

    std::unique_ptr<Button> newGame;
    std::unique_ptr<Button> loadSave;

    // Player (base stats requested)
    Player player{ 100, 5, 0 };

    // Room progression (10 fixed rooms)
    std::vector<GameRoom> rooms;
    std::size_t currentRoomIndex = 0;
    const std::size_t totalRooms = 10;

    // Visuals for the playing state
    sf::RectangleShape doorRect;   // gray rectangle at middle-bottom

    // last drawn enemy bounds (for click detection)
    sf::FloatRect currentEnemyBounds;

    // Room timing and enemy AI
    sf::Clock roomClock; // tracks time since entering current room
    bool enemyNoticed{ false };
    sf::Time lastEnemyAttackTime{ sf::Time::Zero };
    bool playerAttacked{ false }; // whether player attacked the enemy since entering
    // Potions
    int playerPotionCount{ 3 };
    bool roomHasPotion{ false };
    sf::FloatRect potionBounds;
    // Chest
    bool roomHasChest{ false };
    sf::FloatRect chestBounds;
    bool chestOpened{ false };
    // End-of-run timer (for GameOver or Finished state)
    sf::Clock endStateClock;
    bool endStateTimerStarted{ false };

    // Text objects constructed after font load
    std::unique_ptr<sf::Text> roomCounterText;
    std::unique_ptr<sf::Text> playerStatsText;
    std::unique_ptr<sf::Text> congratsText;
    std::unique_ptr<sf::Text> gameOverText;
    // Save system
    SaveSystem saveSystem;

    void saveToSlot(const std::filesystem::path& file);
    bool loadFromSlot(const std::filesystem::path& file);

public:
    MainMenu();

    void startNewGame();
    void handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
};
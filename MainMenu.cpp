#include "MainMenu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <filesystem>

static constexpr unsigned WINDOW_W = 800;
static constexpr unsigned WINDOW_H = 600;

MainMenu::MainMenu()
{
    // Load font (match your SFML usage)
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Font failed to load from 'arial.ttf'\n";
    }
    // seed RNG for potion spawns
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create menu buttons (positions chosen for 800x600)
    newGame = std::make_unique<Button>(font, "New Game", sf::Vector2f{250.f, 60.f}, sf::Vector2f{275.f, 220.f});
    loadSave = std::make_unique<Button>(font, "Load Game", sf::Vector2f{250.f, 60.f}, sf::Vector2f{275.f, 320.f});

    // Setup door rectangle: middle-bottom of the screen
    // Make it vertical and slightly bigger so it's a tall door/portal at bottom
    sf::Vector2f doorSize{80.f, 220.f}; // narrow, tall rectangle near bottom
    doorRect.setSize(doorSize);
    doorRect.setFillColor(sf::Color(150, 150, 150)); // gray
    // setOrigin/setPosition overload taking a single sf::Vector2f is used in this SFML version
    doorRect.setOrigin(sf::Vector2f(doorSize.x / 2.f, doorSize.y / 2.f));
    doorRect.setPosition(sf::Vector2f(static_cast<float>(WINDOW_W) / 2.f, static_cast<float>(WINDOW_H) - doorSize.y / 2.f - 20.f));

    // Prepare text objects (constructed after font is loaded)
    // Allocate sf::Text objects into unique_ptrs using the project's sf::Text constructor order (font, string, size)
    roomCounterText = std::make_unique<sf::Text>(font, "Room 0 / 10", 18);
    roomCounterText->setFillColor(sf::Color::White);
    roomCounterText->setPosition({ 10.f, 10.f });

    playerStatsText = std::make_unique<sf::Text>(font, "", 18);
    playerStatsText->setFillColor(sf::Color::White);
    playerStatsText->setPosition({ 10.f, static_cast<float>(WINDOW_H) - 70.f });

    congratsText = std::make_unique<sf::Text>(font, "Congrats! You beat the dungeon", 32);
    congratsText->setFillColor(sf::Color::White);
    congratsText->setPosition({ 80.f, 280.f });

    gameOverText = std::make_unique<sf::Text>(font, "Game Over - Click to return to Menu", 24);
    gameOverText->setFillColor(sf::Color::Red);
    gameOverText->setPosition({ 120.f, 260.f });

    // Prepare the fixed rooms (empty placeholders)
    rooms.resize(totalRooms);
    for (std::size_t i = 0; i < totalRooms; ++i) rooms[i].id = static_cast<int>(i);
    // Populate each room with either a Skeleton or a Ghost (alternate for predictability)
    for (std::size_t i = 0; i < totalRooms; ++i) {
        if (i % 2 == 0) {
            rooms[i].enemy = std::make_unique<Skeleton>();
        } else {
            rooms[i].enemy = std::make_unique<Ghost>();
        }
    }

    // ensure player starts with requested items when not started; actual assignment will be done on startNewGame
}

void MainMenu::startNewGame()
{
    // Reset rooms (fixed order, nothing random)
    rooms.clear();
    rooms.resize(totalRooms);
    for (std::size_t i = 0; i < totalRooms; ++i) rooms[i].id = static_cast<int>(i);

    // Reset / reinitialize player to the requested base stats
    player = Player{ 100, 5, 0 }; // move-assign a fresh player

    // Give the player the weak armor, weak shield, and simple sword and equip them
    {
        auto armor = std::make_unique<Armor>();
        player.equipItem(*armor);
        player.addItem(std::move(armor));
    }
    {
        auto shield = std::make_unique<Shields>();
        player.equipItem(*shield);
        player.addItem(std::move(shield));
    }
    {
        auto sword = std::make_unique<Swords>();
        player.equipItem(*sword);
        player.addItem(std::move(sword));
    }

    // Reset room index to first room and set state
    currentRoomIndex = 0;
    state = State::Playing;
    // Repopulate rooms with enemies (same deterministic pattern as constructor)
    rooms.clear();
    rooms.resize(totalRooms);
    for (std::size_t i = 0; i < totalRooms; ++i) {
        rooms[i].id = static_cast<int>(i);
        if (i % 2 == 0) {
            rooms[i].enemy = std::make_unique<Skeleton>();
        }
        else {
            rooms[i].enemy = std::make_unique<Ghost>();
        }
    }
    // reset player potion count and potion flags
    playerPotionCount = 3;
    roomHasPotion = false;
    potionBounds = sf::FloatRect();

    // Update counters and stats text
    if (roomCounterText) roomCounterText->setString(sf::String("Room " + std::to_string(currentRoomIndex + 1) + " / " + std::to_string(totalRooms)));
    if (playerStatsText) playerStatsText->setString(sf::String("HP: " + std::to_string(player.getCurrentHP()) + "/" + std::to_string(player.getHP())
        + "  ATT: " + std::to_string(player.getAtt()) + "  DEF: " + std::to_string(player.getDef())));

    std::cout << "New game started. Player created and equipped.\n";
}

void MainMenu::saveToSlot(const std::filesystem::path& file)
{
    SaveData sd;
    sd.setCurrentRoom(static_cast<int>(currentRoomIndex));
    sd.setCurrentStats(Stats(player.getCurrentHP(), player.getAtt(), player.getDef()));

    // copy inventory pointers by creating new items of the same type
    for (const auto& it : player.getInventory()) {
        if (dynamic_cast<HPotion*>(it.get())) sd.addItem(std::make_unique<HPotion>());
        else if (dynamic_cast<Swords*>(it.get())) sd.addItem(std::make_unique<Swords>());
        else if (dynamic_cast<Shields*>(it.get())) sd.addItem(std::make_unique<Shields>());
    }

    saveSystem.saveToFile(file, sd);
}

bool MainMenu::loadFromSlot(const std::filesystem::path& file)
{
    SaveData sd;
    if (!saveSystem.loadSaveFile(file, sd)) return false;

    // restore player stats
    Stats s = sd.getCurrentStats();
    player.setHP(s.HP);
    player.setCurrentHP(s.HP);
    player.setAtt(s.ATT);
    player.setDef(s.DEF);

    // clear player's inventory and add loaded items
    // Note: Player class doesn't expose inventory clear; we will only add items
    for (const auto& it : sd.getCurrentInventory()) {
        // move items from sd into player's inventory
        // sd stores unique_ptrs; but getCurrentInventory returns const refs, so recreate
        if (dynamic_cast<HPotion*>(it.get())) player.addItem(std::make_unique<HPotion>());
        else if (dynamic_cast<Swords*>(it.get())) player.addItem(std::make_unique<Swords>());
        else if (dynamic_cast<Shields*>(it.get())) player.addItem(std::make_unique<Shields>());
    }

    // set current room
    currentRoomIndex = static_cast<std::size_t>(sd.getCurrentRoom());
    if (currentRoomIndex >= rooms.size()) currentRoomIndex = 0;

    return true;
}

void MainMenu::handleEvent(const std::optional<sf::Event>& event, sf::RenderWindow& window)
{
    if (!event) return;

    if (event->is<sf::Event::MouseButtonPressed>())
    {
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(mousePixel);

        if (state == State::Menu)
        {
            if (newGame && newGame->isClicked(mousePos))
            {
                startNewGame();
            }
            else if (loadSave && loadSave->isClicked(mousePos))
            {
                // attempt to load a known save slot file
                std::filesystem::path savePath = std::filesystem::current_path() / "savegame.txt";
                if (loadFromSlot(savePath)) {
                    state = State::Playing;
                    if (roomCounterText) roomCounterText->setString(sf::String("Room " + std::to_string(currentRoomIndex + 1) + " / " + std::to_string(totalRooms)));
                    std::cout << "Loaded save from " << savePath.string() << std::endl;
                } else {
                    std::cout << "Failed to load save file: " << savePath.string() << std::endl;
                }
            }
        }
        else if (state == State::Playing)
        {
            // Click the door (middle bottom) to advance to next room
            // First check if player clicked the enemy
            if (currentRoomIndex < rooms.size() && rooms[currentRoomIndex].enemy && currentEnemyBounds.contains(mousePos))
            {
                Enemy* e = rooms[currentRoomIndex].enemy.get();
                std::string etype = (dynamic_cast<Skeleton*>(e) ? "Skeleton" : (dynamic_cast<Ghost*>(e) ? "Ghost" : "Enemy"));
                // Player attacks enemy when clicked
                int dmg = player.getAtt();
                e->modifyHealth(-dmg);
                // mark that player has attacked this room's enemy
                playerAttacked = true;
                std::cout << "You hit the " << etype << " for " << dmg << " damage. " << std::endl;
                if (!e->isAlive()) {
                    std::cout << etype << " defeated!" << std::endl;
                    rooms[currentRoomIndex].enemy.reset();
                    // clear bounds so further clicks don't register
                    currentEnemyBounds = sf::FloatRect();
                    // reset room AI flags when enemy is defeated
                    enemyNoticed = false;
                    playerAttacked = false;
                    lastEnemyAttackTime = sf::Time::Zero;
                }
            }
            // collect potion if clicked (check before door click)
            else if (roomHasPotion && potionBounds.contains(mousePos)) {
                roomHasPotion = false;
                ++playerPotionCount;
                std::cout << "Picked up a health potion. You now have " << playerPotionCount << " potions." << std::endl;
            }
            // open chest if clicked
            else if (roomHasChest && !chestOpened && chestBounds.contains(mousePos)) {
                chestOpened = true;
                // roll for loot: 30% strong (tier 2), 20% stronger (tier 3)
                int r = rand() % 100; // 0..99
                if (r < 20) {
                    // stronger (tier 3)
                    auto newArmor = std::make_unique<Armor>(3);
                    player.equipItem(*newArmor);
                    player.addItem(std::move(newArmor));
                    // increase player's base stats so hits are harder and they take less damage
                    player.setAtt(player.getAtt() + 4);
                    player.setDef(player.getDef() + 4);
                    std::cout << "You found stronger armor in the chest! ATT+4 DEF+4" << std::endl;
                }
                else if (r < 50) {
                    // strong (tier 2)
                    auto newArmor = std::make_unique<Armor>(2);
                    player.equipItem(*newArmor);
                    player.addItem(std::move(newArmor));
                    player.setAtt(player.getAtt() + 2);
                    player.setDef(player.getDef() + 2);
                    std::cout << "You found strong armor in the chest! ATT+2 DEF+2" << std::endl;
                }
                else {
                    std::cout << "The chest was empty..." << std::endl;
                }
            }
            else if (doorRect.getGlobalBounds().contains(mousePos))
            {
                // Prevent leaving the room if an enemy is still present/alive
                if (currentRoomIndex < rooms.size() && rooms[currentRoomIndex].enemy && rooms[currentRoomIndex].enemy->isAlive()) {
                    std::cout << "You cannot leave while the enemy is alive!" << std::endl;
                }
                else {
                    if (currentRoomIndex + 1 < totalRooms)
                    {
                        ++currentRoomIndex;
                        std::cout << "Moved to room " << currentRoomIndex << '\n';
                    // save on entering a new room
                    saveToSlot(std::filesystem::current_path() / "savegame.txt");
                    }
                    else
                    {
                        // Completed all rooms
                        state = State::Finished;
                        std::cout << "Reached final room, finished dungeon\n";
                    saveToSlot(std::filesystem::current_path() / "savegame.txt");
                    }

                    if (roomCounterText)
                    {
                        roomCounterText->setString(sf::String("Room " + std::to_string(currentRoomIndex + 1) + " / " + std::to_string(totalRooms)));
                    }
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

    // handle keyboard presses (SFML 3 style: events are optionals; keyboard handling here via global state)
    if (state == State::Playing) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
            // use potion if available
            if (playerPotionCount > 0 && player.getCurrentHP() > 0) {
                HPotion potion;
                int cur = player.getCurrentHP();
                potion.use(cur);
                player.setCurrentHP(cur);
                --playerPotionCount;
                std::cout << "Used a health potion. Remaining: " << playerPotionCount << std::endl;
            }
        }
        // also save periodically: upon any key press Q (quit) or when toggling room changes handled above
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            // save current state and exit application
            saveToSlot(std::filesystem::current_path() / "savegame.txt");
            window.close();
        }
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
        // Door at bottom center
        window.draw(doorRect);

        // Handle enemy noticing and automatic attacks
        // If entering a new room, restart clock and flags
        static std::size_t lastRoomIndex = static_cast<std::size_t>(-1);
        if (lastRoomIndex != currentRoomIndex) {
            roomClock.restart();
            enemyNoticed = false;
            playerAttacked = false;
            lastEnemyAttackTime = sf::Time::Zero;
            lastRoomIndex = currentRoomIndex;
        }

        // If there is an enemy and the player hasn't attacked, check for notice
        if (currentRoomIndex < rooms.size() && rooms[currentRoomIndex].enemy) {
            Enemy* e = rooms[currentRoomIndex].enemy.get();
            sf::Time elapsed = roomClock.getElapsedTime();
            // after 2 seconds without player attack, enemy notices player
            if (!enemyNoticed && !playerAttacked && elapsed.asSeconds() >= 2.f) {
                enemyNoticed = true;
                lastEnemyAttackTime = elapsed; // schedule attacks starting now
            }

            // if noticed, enemy attacks once per second
            if (enemyNoticed && e->isAlive()) {
                sf::Time now = roomClock.getElapsedTime();
                // attack once per second starting from lastEnemyAttackTime
                if (now.asSeconds() - lastEnemyAttackTime.asSeconds() >= 1.f) {
                    // enemy deals its attack to the player
                    int dmg = e->getAtt();
                    player.modifyHealth(-dmg);
                    std::cout << "The enemy hits you for " << dmg << " damage because it noticed you." << std::endl;
                    lastEnemyAttackTime = now;
                }
            }
        }

        // Spawn a potion in the room with 15% chance when entering a new room
        static std::size_t potionSpawnedForRoom = static_cast<std::size_t>(-1);
        if (potionSpawnedForRoom != currentRoomIndex) {
            potionSpawnedForRoom = currentRoomIndex;
            roomHasPotion = false;
            potionBounds = sf::FloatRect();
            // 15% chance to spawn a potion
            int roll = rand() % 100; // 0..99
            if (roll < 15) {
                roomHasPotion = true;
                // place left of the door between door and wall
                sf::Vector2f doorPos = doorRect.getPosition();
                sf::Vector2f doorSize = doorRect.getSize();
                // choose a small green box size
                sf::Vector2f psize{20.f, 20.f};
                // place between left wall (x=0) and left edge of door
                float doorLeft = doorPos.x - doorSize.x / 2.f;
                float x = (doorLeft + 20.f) / 2.f; // midpoint between wall and doorLeft, shift a bit
                float y = doorPos.y - doorSize.y / 2.f - psize.y / 2.f; // sit on the floor level (same baseline as door)
                potionBounds = sf::FloatRect(sf::Vector2f(x - psize.x/2.f, y - psize.y/2.f), psize);
            }
            // chest spawn: 25% chance to spawn in back-left corner
            roomHasChest = false;
            int chestRoll = rand() % 100;
            if (chestRoll < 25) {
                roomHasChest = true;
            }
            chestOpened = false;
            // place chest in back-left corner (near top-left but not overlapping UI)
            sf::Vector2f csize{40.f, 30.f};
            float cx = 40.f + csize.x/2.f; // small margin from left wall
            float cy = 80.f + csize.y/2.f; // some margin from top
            chestBounds = sf::FloatRect(sf::Vector2f(cx - csize.x/2.f, cy - csize.y/2.f), csize);
        }

        // Draw enemy in current room (if any) and store its bounds for click detection
        currentEnemyBounds = sf::FloatRect();
        if (currentRoomIndex < rooms.size() && rooms[currentRoomIndex].enemy) {
            Enemy* e = rooms[currentRoomIndex].enemy.get();
            // draw enemy size similar to door
            sf::Vector2f esize = doorRect.getSize();

            // compute positions relative to door: skeleton on the right, ghost on the left, both above the door
            sf::Vector2f doorPos = doorRect.getPosition();
            float padding = 20.f;
            float aboveOffset = doorRect.getSize().y / 2.f + esize.y / 2.f + 10.f; // how far above the door

            if (dynamic_cast<Skeleton*>(e)) {
                // position to the right of the door
                sf::Vector2f epos(doorPos.x + doorRect.getSize().x / 2.f + esize.x / 2.f + padding,
                                  doorPos.y - aboveOffset);

                // draw red rectangle for skeleton sized to door
                sf::RectangleShape r;
                r.setSize(esize);
                r.setFillColor(sf::Color::Red);
                r.setOrigin(r.getSize() / 2.f);
                r.setPosition(epos);
                window.draw(r);
                currentEnemyBounds = r.getGlobalBounds();

                // Draw HP text above the skeleton
                sf::Text hpText(font, sf::String(""), 14);
                hpText.setFillColor(sf::Color::White);
                hpText.setString(sf::String("HP: " + std::to_string(e->getCurrentHP()) + "/" + std::to_string(e->getHP())));
                // center text and place slightly above the enemy
                sf::FloatRect tb = hpText.getLocalBounds();
                hpText.setOrigin(sf::Vector2f(tb.position.x + tb.size.x / 2.f, tb.position.y + tb.size.y / 2.f));
                hpText.setPosition(sf::Vector2f(epos.x, epos.y - esize.y / 2.f - 12.f));
                window.draw(hpText);
            }
            else if (dynamic_cast<Ghost*>(e)) {
                // position to the left of the door
                sf::Vector2f epos(doorPos.x - (doorRect.getSize().x / 2.f + esize.x / 2.f + padding),
                                  doorPos.y - aboveOffset);

                // draw red circle scaled to door width
                float radius = std::max(esize.x, esize.y) / 2.f;
                sf::CircleShape c(radius);
                c.setFillColor(sf::Color::Red);
                c.setOrigin({radius, radius});
                c.setPosition(epos);
                window.draw(c);
                currentEnemyBounds = c.getGlobalBounds();

                // Draw HP text above the ghost
                sf::Text hpText(font, sf::String(""), 14);
                hpText.setFillColor(sf::Color::White);
                hpText.setString(sf::String("HP: " + std::to_string(e->getCurrentHP()) + "/" + std::to_string(e->getHP())));
                sf::FloatRect tb = hpText.getLocalBounds();
                hpText.setOrigin(sf::Vector2f(tb.position.x + tb.size.x / 2.f, tb.position.y + tb.size.y / 2.f));
                hpText.setPosition(sf::Vector2f(epos.x, epos.y - radius - 12.f));
                window.draw(hpText);
            }
        }

        // Draw potion if present
        if (roomHasPotion) {
            sf::RectangleShape pshape;
            sf::Vector2f psize = potionBounds.size;
            pshape.setSize(psize);
            pshape.setFillColor(sf::Color::Green);
            pshape.setOrigin(psize / 2.f);
            pshape.setPosition(sf::Vector2f(potionBounds.position.x + psize.x / 2.f, potionBounds.position.y + psize.y / 2.f));
            window.draw(pshape);
        }

        // Draw chest in back-left corner if present and not opened
        if (roomHasChest && !chestOpened) {
            sf::RectangleShape chestShape;
            sf::Vector2f csize = chestBounds.size;
            chestShape.setSize(csize);
            // medium light brown
            chestShape.setFillColor(sf::Color(181, 101, 29));
            chestShape.setOrigin(csize / 2.f);
            chestShape.setPosition(sf::Vector2f(chestBounds.position.x + csize.x / 2.f, chestBounds.position.y + csize.y / 2.f));
            window.draw(chestShape);
        }

        // Room counter
        if (roomCounterText) window.draw(*roomCounterText);

        // Update and draw player stats in bottom-left
        if (playerStatsText) {
            playerStatsText->setString(sf::String("HP: " + std::to_string(player.getCurrentHP()) + "/" + std::to_string(player.getHP())
                + "  ATT: " + std::to_string(player.getAtt()) + "  DEF: " + std::to_string(player.getDef())));
            window.draw(*playerStatsText);
        }
        // If player died, transition to GameOver
        if (!player.isAlive()) {
            state = State::GameOver;
        }
    }
    else if (state == State::Finished)
    {
        if (congratsText) window.draw(*congratsText);
        // start timer to return to menu automatically
        if (!endStateTimerStarted) {
            endStateClock.restart();
            endStateTimerStarted = true;
        }
        if (endStateTimerStarted && endStateClock.getElapsedTime().asSeconds() >= 3.f) {
            state = State::Menu;
            endStateTimerStarted = false;
        }
    }
    else if (state == State::GameOver)
    {
        if (gameOverText) window.draw(*gameOverText);
        if (!endStateTimerStarted) {
            endStateClock.restart();
            endStateTimerStarted = true;
        }
        if (endStateTimerStarted && endStateClock.getElapsedTime().asSeconds() >= 3.f) {
            state = State::Menu;
            endStateTimerStarted = false;
        }
    }
}       
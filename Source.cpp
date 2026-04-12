#include <SFML/Graphics.hpp>
#include "MainMenu.h"

int main()
{
    // construct VideoMode with a Vector2u and use sf::String for title to match this SFML version
    sf::VideoMode vm(sf::Vector2u{800u, 600u});
    sf::RenderWindow window(vm, sf::String("Game"));

    MainMenu menu;

    while (window.isOpen())
    {
        // SFML 3: pollEvent returns std::optional<sf::Event>
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            menu.handleEvent(event, window);
        }

        window.clear();
        menu.draw(window);
        window.display();
    }

    return 0;
}
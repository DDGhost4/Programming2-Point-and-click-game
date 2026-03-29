#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    Button(const sf::Font& font, const std::string& str, sf::Vector2f size, sf::Vector2f position);

    void draw(sf::RenderWindow& window);
    bool isClicked(sf::Vector2f mousePos) const;
};
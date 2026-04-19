#include "Button.h"

Button::Button(const sf::Font& font, const std::string& str, sf::Vector2f size, sf::Vector2f position)
    : text(font, str, 28) // original ordering (font first) used in this project
{
    shape.setSize(size);
    shape.setFillColor(sf::Color(80, 80, 80));
    shape.setPosition(position);

    text.setFillColor(sf::Color::White);

    // setPosition takes a single sf::Vector2f in this SFML version
    float x = position.x + size.x / 2.f - 10.f;
    float y = position.y + (size.y - static_cast<float>(text.getCharacterSize())) / 2.f;
    text.setPosition(sf::Vector2f{x, y});
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(sf::Vector2f mousePos) const
{
    return shape.getGlobalBounds().contains(mousePos);
}
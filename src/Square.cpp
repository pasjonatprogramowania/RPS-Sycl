#include "Square.hpp"

Square::Square(float x, float y, std::string colour, float size) : x(x), y(y), colour(colour) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(size, size));
    setColor(colour);
}

void Square::setColor(const std::string& colour) {
    this->colour = colour;
    if (colour == "red")
        shape.setFillColor(sf::Color::Red);
    else if (colour == "green")
        shape.setFillColor(sf::Color::Green);
    else if (colour == "blue")
        shape.setFillColor(sf::Color::Blue);
    else
        shape.setFillColor(sf::Color::White); // Default color if not recognized
}

std::string Square::getColor() const {
    return colour;
}

void Square::draw(sf::RenderWindow& window) const{
    window.draw(shape);
}

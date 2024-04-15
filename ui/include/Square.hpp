#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Square {
public:
    Square(float x, float y, std::string colour, float size);
    virtual ~Square() = default;

    void setColor(const std::string& colour);
    std::string getColor() const;
    void draw(sf::RenderWindow& window) const;
    void move(const float x, const float y);

private:
    sf::RectangleShape shape;
    float x, y;
    std::string colour;
};

#endif // SQUARE_HPP

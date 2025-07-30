//
// Created by dawud on 28/07/2025.
//

#ifndef LINE_H
#define LINE_H
#include "SFML/Graphics.hpp"



class Line {
private:
    sf::Vector2f start; // Start point of the line
    sf::Vector2f end; // End point of the line
    sf::Color color; // Color of the line
    float thickness; // Thickness of the line
    sf::RectangleShape lineShape; // SFML shape to represent the line
    void updateLineShape(); // Updates the line shape based on start, end, color, and thickness
public:
    Line(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color, float thickness);

    void draw(sf::RenderTarget& target) const;
    void setStart(const sf::Vector2f& newStart);
    void setEnd(const sf::Vector2f& newEnd);
    void setColor(const sf::Color& newColor);
    void setThickness(float newThickness);
};



#endif //LINE_H

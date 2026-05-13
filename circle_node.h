//
// Created by dawud on 17/07/2025.
//

#ifndef CIRCLENODE_H
#define CIRCLENODE_H
#include "SFML/Graphics.hpp"


class CircleNode {
private:
    sf::CircleShape circle;

public:
    CircleNode(); // Default constructor
    CircleNode(float radius, const sf::Color& color);
    void setPosition(float x, float y);
    void setRadius(float radius);
    void setFillColor(const sf::Color& color);
    sf::Vector2f getPosition() const;
    float getRadius() const;
    sf::Color getFillColor() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif //CIRCLENODE_H

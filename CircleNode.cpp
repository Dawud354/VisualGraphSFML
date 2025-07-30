//
// Created by dawud on 17/07/2025.
//

#include "CircleNode.h"

CircleNode::CircleNode() {
    circle.setRadius(50.0f); // Default radius
    circle.setFillColor(sf::Color::Green); // Default color
}

CircleNode::CircleNode(const float radius, const sf::Color& color) {
    circle.setRadius(radius);
    circle.setFillColor(color);
}

void CircleNode::setPosition(const float x, const float y) {
    circle.setPosition(x, y);
}

void CircleNode::setRadius(const float radius) {
    circle.setRadius(radius);
}

void CircleNode::setFillColor(const sf::Color& color) {
    circle.setFillColor(color);
}

sf::Vector2f CircleNode::getPosition() const {
    return circle.getPosition();
}

float CircleNode::getRadius() const {
    return circle.getRadius();
}

sf::Color CircleNode::getFillColor() const {
    return circle.getFillColor();
}

void CircleNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(circle, states);
}


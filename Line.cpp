//
// Created by dawud on 28/07/2025.
//

#include "Line.h"
#include <cmath>

Line::Line(const sf::Vector2f& start, const sf::Vector2f& end, const sf::Color& color, float thickness)
    : start(start), end(end), color(color), thickness(thickness) {
    updateLineShape(); // Initialize the line shape
}

void Line::draw(sf::RenderTarget& target) const {
    target.draw(lineShape); // Draw the line shape
}

void Line::updateLineShape() {
    // Calculate the angle of the line
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f; // Convert radians to degrees
    // Create a rectangle shape to represent the line
    lineShape.setSize(sf::Vector2f(length, thickness));
    lineShape.setFillColor(color);
    lineShape.setPosition(start);
    lineShape.setRotation(angle); // Rotate the line to the correct angle
    lineShape.setOrigin(0, thickness / 2); // Set the origin to the left center for proper rotation

}

void Line::setStart(const sf::Vector2f& newStart) {
    start = newStart;
    updateLineShape(); // Update the line shape after changing the start point
}

void Line::setEnd(const sf::Vector2f& newEnd) {
    end = newEnd;
    updateLineShape(); // Update the line shape after changing the end point
}

void Line::setColor(const sf::Color& newColor) {
    color = newColor;
    lineShape.setFillColor(color); // Update the color of the line shape
}

void Line::setThickness(float newThickness) {
    thickness = newThickness;
    updateLineShape(); // Update the line shape after changing the thickness
}



// Note: The Line class can be used
// to draw lines between circles in the CircleGraph or CircleNodeBox classes.
// It can be integrated into the CircleGraph::draw method to visualize connections between circles.
// The Line class provides a simple way to represent and draw lines in SFML,
// making it easy to connect CircleNodes visually.


//
// Created by dawud on 17/07/2025.
//

#include "CircleNodeBox.h"

#include <iostream>


CircleNodeBox::CircleNodeBox(const float x, const float y, const float width, const float height, const sf::Color& boxColor) {
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(boxColor);
    box.setOutlineColor(sf::Color::Black);
}

void CircleNodeBox::setPosition(float x, float y) {
    box.setPosition(x, y);
}

void CircleNodeBox::addCircle(float radius, const sf::Color& color) {
    const sf::String label = "Circle " + std::to_string(circleGraph.getCircleCount() + 1);
    std::cout << "Adding circle with label: " << label.toAnsiString() << std::endl;
    circleGraph.addCircle(label, radius, color, box.getPosition().x + box.getSize().x / 2 - radius, box.getPosition().y + box.getSize().y / 2 - radius);
    currentMessage = CircleNodeBoxMessages::ADDED_CIRCLE; // Set message to added circle
}

void CircleNodeBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(box, states);
    circleGraph.draw(target, states); // Draw the circles in the box
}

void CircleNodeBox::updateCirclePositions(const sf::RenderWindow& window) {
    for (auto& circle : circleGraph.getCircles()) {
        if (checkIfMouseInsideCircle(window, circle)) {
            currentCircle = circle; // Update current circle being interacted with
            updateCirclePositionBasedOnMouse(window, circle);
            break; // Only update the first circle that the mouse is inside
        }
    }
}


void CircleNodeBox::removeCircle(const sf::RenderWindow& window) {
    currentMessage = CircleNodeBoxMessages::NOTHING_DONE; // Reset message to NONE
    if (circleGraph.getCircleCount() == 0) {
        std::cout << "No circles to remove." << std::endl;
        return; // No circles to remove
    }
    if (isDeleting) {
        for (const std::string& currentCircle : circleGraph.getCircles()) {
            if (checkIfMouseInsideCircle(window, currentCircle)) {
                circleGraph.removeCircle(currentCircle);
                currentMessage = CircleNodeBoxMessages::REMOVED_CIRCLE; // Set message to removed circle
                isDeleting = false; // Exit delete mode after removing a circle
            }
        }
    }
}


// Check if mouse is inside a circle
bool CircleNodeBox::checkIfMouseInsideCircle(const sf::RenderWindow &window, const std::string& circle) const {
    // get mouse and circle position
    const sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    float radius = circleGraph.getCircleRadius(circle);
    const sf::Vector2f circleCentre = circleGraph.getCirclePosition(circle) + sf::Vector2f(radius, radius);
    // more efficient distance check
    float dx = mousePosition.x - circleCentre.x;
    float dy = mousePosition.y - circleCentre.y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSquared = radius * radius;
    if (distanceSquared <= radiusSquared) {
        return true;
    }
    return false;
}

void CircleNodeBox::updateCirclePositionBasedOnMouse(const sf::RenderWindow& window, const std::string& circle) {
    const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    circleGraph.setCirclePosition(
        circle,
        static_cast<float>(mousePosition.x) - circleGraph.getCircleRadius(circle),
        static_cast<float>(mousePosition.y) - circleGraph.getCircleRadius(circle)
    );
    // Ensure circle stays within box bounds
    float circleRadius = circleGraph.getCircleRadius(circle);
    if (circleGraph.getCirclePosition(circle).x<box.getPosition().x) {
        circleGraph.setCirclePosition(circle,box.getPosition().x, circleGraph.getCirclePosition(circle).y);
    }
    if (circleGraph.getCirclePosition(circle).y < box.getPosition().y) {
        circleGraph.setCirclePosition(circle,circleGraph.getCirclePosition(circle).x, box.getPosition().y);
    }
    if (circleGraph.getCirclePosition(circle).x + circleRadius * 2 > box.getPosition().x + box.getSize().x) {
        circleGraph.setCirclePosition(circle,box.getPosition().x+box.getSize().x - circleRadius * 2, circleGraph.getCirclePosition(circle).y);
    }
    if (circleGraph.getCirclePosition(circle).y + circleRadius * 2 > box.getPosition().y + box.getSize().y) {
        circleGraph.setCirclePosition(circle,circleGraph.getCirclePosition(circle).x, box.getPosition().y + box.getSize().y - circleRadius * 2);
    }
}

void CircleNodeBox::setIsDeleting(bool deleting) {
    isDeleting = deleting;
}

bool CircleNodeBox::getIsDeleting() const {
    return isDeleting;
}

CircleNodeBoxMessages CircleNodeBox::getCurrentMessage() const {
    return currentMessage;
}

// Implement connection logic here
void CircleNodeBox::connectCircles(const sf::RenderWindow& window) {
    std::cout << "Connecting circles..." << std::endl;
    currentMessage = CircleNodeBoxMessages::NOTHING_DONE; // Reset message to NONE
    for (const std::string& currentCircle : circleGraph.getCircles()) {
        if (checkIfMouseInsideCircle(window, currentCircle)) {
            if (previousClickedCircle.empty()) {
                previousClickedCircle = currentCircle; // Store the first clicked circle
                currentMessage = CircleNodeBoxMessages::SELECTED_ONE_CIRCLE_TO_CONNECT; //Nothing done
            } else {
                if (currentCircle != previousClickedCircle) { // Ensure not connecting to itself
                    circleGraph.addEdge(previousClickedCircle, currentCircle); // Connect the circles
                    currentMessage = CircleNodeBoxMessages::CONNECTED_CIRCLES; // Set message to connected circles
                }
                previousClickedCircle.clear(); // Reset after connecting
            }
        }
    }
}

void CircleNodeBox::disconnectCircles(const sf::RenderWindow& window) {
    currentMessage = CircleNodeBoxMessages::NOTHING_DONE; // Reset message to NONE
    for (const std::string& currentCircle : circleGraph.getCircles()) {
        if (checkIfMouseInsideCircle(window, currentCircle)) {
            if (previousClickedCircle.empty()) {
                previousClickedCircle = currentCircle; // Store the first clicked circle
                currentMessage = CircleNodeBoxMessages::SELECTED_ONE_CIRCLE_TO_DISCONNECT; //Nothing done
            } else {
                if (currentCircle != previousClickedCircle) { // Ensure not disconnect to itself
                    circleGraph.removeEdge(previousClickedCircle, currentCircle); // Connect the circles
                    currentMessage = CircleNodeBoxMessages::DISCONNECTED_CIRCLES; // Set message to disconnect circles
                }
                previousClickedCircle.clear(); // Reset after connecting
            }
        }
    }
}

bool CircleNodeBox::canConnectOrDisconnectCircles() const {
    return circleGraph.getCircleCount() >= 2; // At least two circles are needed to connect or disconnect
}

bool CircleNodeBox::canRemoveCircle() const {
    return circleGraph.getCircleCount() > 0; // At least one circle is needed to remove
}

std::string CircleNodeBox::getCircleLabelAtMousePosition(const sf::RenderWindow& window) const {
    for (const std::string& circle : circleGraph.getCircles()) {
        if (checkIfMouseInsideCircle(window, circle)) {
            return circle; // Return the label of the circle at mouse position
        }
    }
    return ""; // Return empty string if no circle is found at mouse position
}

std::vector<std::string> CircleNodeBox::getCircleNeighbours(const std::string& circleLabel) const {
    return circleGraph.getCircleNeighbours(circleLabel); // Return the neighbours of the specified circle
}

std::string CircleNodeBox::getCurrentCircle() const {
    return currentCircle; // Return the current circle being interacted with
}

void CircleNodeBox::updateCircleName(const std::string& oldName, const std::string& newName) {
    circleGraph.changeCircleLabel(oldName, newName); // Update the circle label in the graph
}


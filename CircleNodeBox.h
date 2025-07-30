//
// Created by dawud on 17/07/2025.
// This is to store circles in a box so they are contained
//

#ifndef CIRCLENODEBOX_H
#define CIRCLENODEBOX_H
#include "CircleGraph.h"
#include "SFML/Graphics.hpp"
#include "CircleNode.h"
#include "CircleNodeBoxMessages.h"


class CircleNodeBox {
private:
    sf::RectangleShape box; // Box to contain circles
    std::string previousClickedCircle; // Stores the last clicked circle's label which is used to connect or disconnect circles
    std::string currentCircle; // Stores the current circle being interacted with
    CircleGraph circleGraph; // CircleGraph to manage circles
    CircleNodeBoxMessages currentMessage; // Current message type for the box
    bool isDeleting = false; // Flag to indicate if a circle should be deleted
    bool checkIfMouseInsideCircle(const sf::RenderWindow &window, const std::string& circle) const;
    void updateCirclePositionBasedOnMouse(const sf::RenderWindow& window, const std::string& circle);
public:
    CircleNodeBox(float x,float y,float width, float height, const sf::Color& boxColor);
    void setPosition(float x, float y);
    void addCircle(float radius, const sf::Color& color);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void updateCirclePositions(const sf::RenderWindow& window);
    std::string getCircleLabelAtMousePosition(const sf::RenderWindow& window) const;
    std::vector<std::string> getCircleNeighbours(const std::string& circleLabel) const;
    void removeCircle(const sf::RenderWindow& window);
    void connectCircles(const sf::RenderWindow& window);
    void disconnectCircles(const sf::RenderWindow& window);
    void setIsDeleting(bool deleting);
    bool getIsDeleting() const;
    CircleNodeBoxMessages getCurrentMessage() const;
    bool canConnectOrDisconnectCircles() const;
    bool canRemoveCircle() const;
    std::string getCurrentCircle() const;
    void updateCircleName(const std::string& oldName, const std::string& newName);
};



#endif //CIRCLENODEBOX_H

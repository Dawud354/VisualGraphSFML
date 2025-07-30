#include "TextBox.h"
#include <CircleNode.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <CircleNodeBox.h>
#include "MainFrame.h"
#include "Graph.h"

#include "Line.h"
#include "Button.h"
#include "UserInteractionBox.h"


// Check if mouse is inside a circle
bool checkIfMouseInsideCircle(const sf::RenderWindow &window, const sf::CircleShape &circle) {
    // get mouse and circle position
    const sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    const sf::Vector2f circleCentre = circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius());
    // more efficient distance check
    float dx = mousePosition.x - circleCentre.x;
    float dy = mousePosition.y - circleCentre.y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSquared = circle.getRadius() * circle.getRadius();
    if (distanceSquared <= radiusSquared) {
        return true;
    }
    return false;
}

void updateCirclePositionBasedOnMouse(const sf::RenderWindow& window, sf::CircleShape& circle) {
    const sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    circle.setPosition(
        static_cast<float>(mousePosition.x) - circle.getRadius(),
        static_cast<float>(mousePosition.y) - circle.getRadius()
    );

    // Ensure circle stays within box bounds
    if (circle.getPosition().x<0) {
        circle.setPosition(0, circle.getPosition().y);
    }
    if (circle.getPosition().y < 0) {
        circle.setPosition(circle.getPosition().x, 0);
    }
    if (circle.getPosition().x + circle.getRadius() * 2 > window.getSize().x) {
        circle.setPosition(window.getSize().x - circle.getRadius() * 2, circle.getPosition().y);
    }
    if (circle.getPosition().y + circle.getRadius() * 2 > window.getSize().y) {
        circle.setPosition(circle.getPosition().x, window.getSize().y - circle.getRadius() * 2);
    }
}

void addCircleToBox(CircleNodeBox& circleBox, float radius, const sf::Color& color) {
    circleBox.addCircle(radius, color);
}



int main()
{

    // sf::RenderWindow window(sf::VideoMode(800, 600), "Empty SFML Window");
    // window.setFramerateLimit(60); // Cap to 60 FPS
    // TextBox tb(10, 10, 200, 50, sf::Color(200, 200, 200));
    // TextBox tb2(10, 70, 200, 50, sf::Color(200, 200, 200));
    //
    //     while (window.isOpen()) {
    //         sf::Event event;
    //         while (window.pollEvent(event)) {
    //             if (event.type == sf::Event::Closed) {
    //                 window.close();
    //             } else if (event.type == sf::Event::KeyPressed) {
    //                 if (event.key.code == sf::Keyboard::M) {
    //                     std::cout << "input box: "<<tb.getInputText() << std::endl;
    //                 }
    //             }
    //
    //             if (event.type == sf::Event::TextEntered) {
    //                 std::cout << "Key Pressed: " << static_cast<char>(event.text.unicode) << std::endl;
    //                 tb.handleInput(event); // Handle input for the text box
    //                 tb2.handleInput(event); // Handle input for the second text box
    //
    //             }
    //
    //             if (event.type == sf::Event::MouseButtonPressed) {
    //                 if (event.mouseButton.button == sf::Mouse::Left) {
    //                     if (tb.isClicked(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
    //                         std::cout << "Text box 1 clicked!" << std::endl;
    //                     }
    //                     if (tb2.isClicked(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
    //                         std::cout << "Text box 2 clicked!" << std::endl;
    //                     }
    //                 }
    //             }
    //         }
    //         if (tb.getIsActive() || tb2.getIsActive()) {
    //             window.setKeyRepeatEnabled(false); // Enable key repeat when text box is active
    //         } else {
    //             window.setKeyRepeatEnabled(true); // Disable key repeat when text box is not active
    //         }
    //
    //         window.clear();
    //         // Draw the lines
    //
    //         tb.draw(window); // Draw the text box
    //         tb2.draw(window); // Draw the second text box
    //         // Draw the instructions box
    //         window.display();
    //     }

    MainFrame mainFrame; // Create an instance of MainFrame
    mainFrame.run(); // Run the main frame
    return 0;

    // Graph graph;
    // graph.addNode("A");
    // graph.addNode("B");
    // graph.addNode("C");
    // std::cout << "Graph before changing: \n" << graph.toString() << std::endl;
    // graph.updateNodeLabel("A","D");
    // std::cout << "Graph after changing:\n " << graph.toString() << std::endl;


}

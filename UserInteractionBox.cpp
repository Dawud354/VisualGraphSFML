//
// Created by dawud on 21/07/2025.
//

#include "UserInteractionBox.h"

#include <iostream>

#include "FontManager.h"

UserInteractionBox::UserInteractionBox(float x, float y, float width, float height, const sf::Color &boxColor){
    // Set up the background
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(220, 220, 220)); // Lighter color for contrast

    nodeDescriptionBox.setPosition(x + 10, y + 10);
    nodeDescriptionBox.setSize(sf::Vector2f(width - 20, height / 3 - 20));
    nodeDescriptionBox.setFillColor(sf::Color(240, 240, 240)); // Slightly lighter for visibility
    nodeDescriptionBox.setOutlineColor(sf::Color::Black);

    instructionsBox.setPosition(x + 10, height - height / 3);
    instructionsBox.setSize(width - 20, height / 3);
    instructionsBox.setFillColor(sf::Color(240, 240, 240)); // Slightly lighter for visibility
    instructionsBox.setText("Click a button to interact with the circles"); // Default instructions text

    float buttonWidth = (width - 30) / 2; // Width of the buttons
    sf::Vector2f nodeDescriptionBoxBottomLeft = nodeDescriptionBox.getPosition() +
                                                sf::Vector2f(0, nodeDescriptionBox.getSize().y);

    sf::Vector2f instructionsBoxTopLeft = instructionsBox.getPosition();
    float buttonHeight = (instructionsBoxTopLeft.y - nodeDescriptionBoxBottomLeft.y - 30) / 2; // Height of the buttons

    Button button1("Add node", x + 10, nodeDescriptionBoxBottomLeft.y + 10, buttonWidth, buttonHeight, sf::Color::Green,
                   sf::Color::Black, [&]() { addCircle(); });
    Button button2("Remove node", x + 20 + buttonWidth, nodeDescriptionBoxBottomLeft.y + 10, buttonWidth, buttonHeight,
                   sf::Color::Red, sf::Color::White, [&]() { removeCircle(); });
    Button button3("Connect nodes", x + 10, nodeDescriptionBoxBottomLeft.y + 20 + buttonHeight, buttonWidth,
                   buttonHeight, sf::Color::Blue, sf::Color::White, [&]() { connectNodes(); });
    Button button4("Disconnect nodes", x + 20 + buttonWidth, nodeDescriptionBoxBottomLeft.y + 20 + buttonHeight,
                   buttonWidth, buttonHeight, sf::Color::Yellow, sf::Color::Black, [&]() { disconnectNodes(); });
    buttons["Remove node"] = button2;
    buttons["Connect nodes"] = button3;
    buttons["Disconnect nodes"] = button4;
    buttons["Add node"] = button1;

    // Set up the buttons

    currentMessage = UserInteractionMessages::DRAG_CIRCLE; // Initialize current message to NONE

    setNodeDescription("",std::vector<std::string>()); // Initialize node description with empty values
}

void UserInteractionBox::draw(sf::RenderWindow &target, sf::RenderStates states) const {
    target.draw(background, states); // Draw the background first
    target.draw(nodeDescriptionBox, states); // Draw the node description box
    instructionsBox.draw(target, states); // Draw the instructions box
    nodeNameText.draw(target, states); // Draw the node name label
    neighboursText.draw(target, states); // Draw the neighbours label
    nodeNameTextBox.draw(target, states); // Draw the node name text box

    // Draw all buttons
    for (const auto &pair: buttons) {
        pair.second.draw(target, states);
    }
}

void UserInteractionBox::addCircle() {
    std::cout << "Add Circle button clicked" << std::endl;
    // Implement the logic to add a circle
    currentMessage = UserInteractionMessages::ADD_CIRCLE; // Set the current message to ADD_CIRCLE
    instructionsBox.setText("Adding a new circle"); // Update instructions box text
}

void UserInteractionBox::removeCircle() {
    std::cout << "Remove Circle button clicked" << std::endl;
    // Implement the logic to remove a circle
    currentMessage = UserInteractionMessages::REMOVE_CIRCLE; // Set the current message to REMOVE_CIRCLE
    instructionsBox.setText("Click to remove a circle"); // Update instructions box text
}

void UserInteractionBox::connectNodes() {
    std::cout << "Connect Nodes button clicked" << std::endl;
    // Implement the logic to connect two nodes
    currentMessage = UserInteractionMessages::CONNECT_CIRCLES; // Set the current message to CONNECT_CIRCLES
    instructionsBox.setText("Click two circles to connect them"); // Update instructions box text
}

void UserInteractionBox::disconnectNodes() {
    std::cout << "Disconnect Nodes button clicked" << std::endl;
    currentMessage = UserInteractionMessages::DISCONNECT_CIRCLES; // Set the current message to DISCONNECT_CIRCLES
    instructionsBox.setText("Click two circles to disconect them them"); // Update instructions box text

}

void UserInteractionBox::handleButtonClick(sf::RenderWindow &window) {
    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (nodeNameTextBox.isClicked(mousePosition)) {
        window.setKeyRepeatEnabled(false); // Disable key repeat when text box is active
        currentMessage = UserInteractionMessages::EDIT_CIRCLE_NAME;
        instructionsBox.setText("Edit the circle name and press Enter \nto save the new name"); // Update instructions box text
        return; // Exit early if the text box is clicked
    } else if (currentMessage == UserInteractionMessages::EDIT_CIRCLE_NAME) {
        currentMessage = UserInteractionMessages::DRAG_CIRCLE; // Reset to drag mode if text box is not clicked
    }
    else {
        window.setKeyRepeatEnabled(true); // Enable key repeat when text box is not active
    }
    for (auto &pair: buttons) {
        pair.second.handleClick(mousePosition);
    }
}

UserInteractionMessages UserInteractionBox::getCurrentMessage() const {
    return currentMessage; // Return the current message type
}

void UserInteractionBox::goIntoDragMode() {
    currentMessage = UserInteractionMessages::DRAG_CIRCLE; // Set the current message to DRAG_CIRCLE
    instructionsBox.setText("Click and drag a circle to move it"); // Update instructions box text
}

void UserInteractionBox::disableRemoveCircle() {
    buttons["Remove node"].disableButton(); // Disable the remove circle button
}

void UserInteractionBox::disableConnectNodes() {
    buttons["Connect nodes"].disableButton(); // Disable the connect nodes button
}

void UserInteractionBox::disableDisconnectNodes() {
    buttons["Disconnect nodes"].disableButton(); // Disable the disconnect nodes button
}

void UserInteractionBox::enableRemoveCircle() {
    buttons["Remove node"].enableButton(); // Enable the remove circle button
}

void UserInteractionBox::enableConnectNodes() {
    buttons["Connect nodes"].enableButton(); // Enable the connect nodes button
}

void UserInteractionBox::enableDisconnectNodes() {
    buttons["Disconnect nodes"].enableButton(); // Enable the disconnect nodes button
}

void UserInteractionBox::setNodeDescription(const std::string& nodeName, const std::vector<std::string> &neighbours) {
    oldCircleName = nodeName; // Store the old circle name for text input

    nodeNameText.setText("Name: ");
    nodeNameText.setPosition(nodeDescriptionBox.getPosition().x + 10, nodeDescriptionBox.getPosition().y + 10);


    nodeNameTextBox.setInputText(nodeName); // Set the node name in the text box
    nodeNameTextBox.setPosition(nodeNameText.getPosition().x + nodeNameText.getSize().x + 10, nodeDescriptionBox.getPosition().y + 10);
    nodeNameTextBox.setSize(nodeDescriptionBox.getSize().x - nodeNameText.getSize().x - 20, nodeNameText.getSize().y); // Adjust size based on text length

    std::string description = "Neighbours: ";
    for (const auto &neighbour: neighbours) {
        description += neighbour + " ";
    }
    if (neighbours.empty()) {
        description += "None"; // If no neighbours, indicate that
    }
    neighboursText.setText(description);
    neighboursText.setPosition(nodeDescriptionBox.getPosition().x + 10, nodeNameText.getPosition().y + nodeNameText.getSize().y + 10);
}

void UserInteractionBox::handleTextInput(sf::Event Event) {
    nodeNameTextBox.handleInput(Event); // Handle input for the text box
}

std::vector<std::string> UserInteractionBox::getTextBoxInput()  {
    std::vector input = {oldCircleName, nodeNameTextBox.getInputText()};
    oldCircleName = nodeNameTextBox.getInputText(); // Update the old circle name with the current input text
    return input;
}

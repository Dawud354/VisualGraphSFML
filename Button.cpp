//
// Created by dawud on 18/07/2025.
//

#include "Button.h"
#include "FontManager.h"

#include <iostream>

Button::Button() {
    this->buttonLabel.setFont(getSharedFont()); // Use a default font, or load a specific one if needed
    this->buttonLabel.setCharacterSize(24);
    this->buttonLabel.setFillColor(sf::Color::Black);
    this->buttonLabel.setString("Default");
    this->buttonLabel.setPosition(0, 0); // Initial position, will be centered later

    shape.setSize(sf::Vector2f(100, 50));
    shape.setFillColor(sf::Color::White);
    normalFillColor = sf::Color::White; // Store the normal fill color
    shape.setOutlineColor(sf::Color::Black);
}

Button::Button(const sf::String &label, const float x, const float y, const float width, const float height,
               const sf::Color &color, const sf::Color &textColor, const std::function<void()> &onClick){
    this->onClickCallback = onClick; // Store the callback function for button click events
    this->buttonLabel.setFont(getSharedFont()); // Use a shared font from FontManager
    this->buttonLabel.setString(label);
    this->buttonLabel.setCharacterSize(24);
    this->buttonLabel.setFillColor(textColor);
    this->buttonLabel.setPosition(x, y); // Initial position, will be centered later
    //centreLabel();

    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    normalFillColor = color; // Store the normal fill color
    shape.setOutlineColor(sf::Color::Black);
}

void Button::centreLabel() {
    sf::Vector2f shapeSize = shape.getSize();
    sf::Vector2f shapePosition = shape.getPosition();
    buttonLabel.setPosition(
        shapePosition.x + shapeSize.x / 2,
        shapePosition.y + shapeSize.y / 2
    );
}

void Button::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

void Button::setSize(float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
}

void Button::setFillColor(const sf::Color &color) {
    shape.setFillColor(color);
}

sf::Vector2f Button::getPosition() const {
    return shape.getPosition();
}

sf::Vector2f Button::getSize() const {
    return shape.getSize();
}

sf::Color Button::getFillColor() const {
    return shape.getFillColor();
}

sf::Text Button::getLabel() const {
    return buttonLabel;
}

void Button::setLabel(const sf::String &label) {
    this->buttonLabel.setString(label);
    centreLabel();
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape, states);
    target.draw(buttonLabel, states);
}

void Button::handleClick(const sf::Vector2f &mousePosition) {
    // Check if the mouse position is within the button's bounds
    if (shape.getGlobalBounds().contains(mousePosition)) {
        if (onClickCallback) {
            onClickCallback(); // Call the callback function if it exists
        }
    }
}

void Button::disableButton() {
    enabled = false;
    shape.setFillColor(sf::Color(200, 200, 200)); // Change color to indicate disabled state
}

void Button::enableButton() {
    enabled = true;
    shape.setFillColor(normalFillColor); // Reset color to normal state
}

bool Button::isEnabled() const {
    return enabled;
}



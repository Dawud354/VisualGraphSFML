//
// Created by dawud on 18/07/2025.
//

#ifndef BUTTON_H
#define BUTTON_H
#include <functional>

#include "SFML/Graphics.hpp"
#include "SFML/System/String.hpp"
#include <memory>


class Button {
private:
    sf::Text buttonLabel; // Button label
    sf::RectangleShape shape; // Button shape
    void centreLabel(); // Centre the label within the button shape
    std::function<void()> onClickCallback; // Callback function for button click events
    sf::Color normalFillColor; // Fill color of the button
    bool enabled = true; // Flag to indicate if the button is enabled or disabled
public:
    Button(const sf::String& label, float x, float y, float width, float height, const sf::Color& boxColor, const sf::Color& textColor,
           const std::function<void()> &onClick = nullptr);
    Button(); // Default constructor
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setFillColor(const sf::Color& color);
    void setLabel(const sf::String& label);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::Color getFillColor() const;
    sf::Text getLabel() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void handleClick(const sf::Vector2f& mousePosition);

    void disableButton();
    void enableButton();
    bool isEnabled() const;

};




#endif //BUTTON_H

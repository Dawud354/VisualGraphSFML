//
// Created by dawud on 29/07/2025.
//

#include "TextBox.h"
#include "FontManager.h"


TextBox::TextBox(float x, float y, float width, float height, const sf::Color& color){
    isActive = false; // Initially not active
    inputText = ""; // Initialize input text as empty

    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(color);

    font = getSharedFont();
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    setPosition(x, y); // Set the position of the text box
}

TextBox::TextBox() {
    // Default constructor initializes an empty text box
    isActive = false; // Initially not active
    inputText = ""; // Initialize input text as empty

    box.setSize(sf::Vector2f(200, 50)); // Default size
    box.setFillColor(sf::Color(220, 220, 220)); // Default color

    font = getSharedFont();
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    setPosition(10, 10); // Default position
}

bool TextBox::isClicked(const sf::Vector2f& mousePosition) {
    if ( box.getGlobalBounds().contains(mousePosition))
    {
        isActive = true; // Set active if mouse is inside the box

        return true; // Mouse is inside the box
    }
    isActive = false; // Set inactive if mouse is outside the box
    return false; // Mouse is outside the box;
}

void TextBox::handleInput(const sf::Event &event) {
    if (!isActive) {
        return; // Only handle input if the text box is active
    }
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            // Only handle ASCII characters
            if (event.text.unicode == '\b') {
                // Handle backspace
                if (!inputText.empty()) {
                    inputText.pop_back(); // Remove last character
                }
            } else if (event.text.unicode == '\r') {
                // Handle enter key
                isActive = false; // Deactivate on enter
            } else {
                inputText += static_cast<char>(event.text.unicode); // Append character
            }
            text.setString(inputText); // Update text display
        }
    }
}

void TextBox::draw(sf::RenderWindow& window, const sf::RenderStates &states) const {
    window.draw(box,states); // Draw the box
    window.draw(text,states); // Draw the text
}

bool TextBox::getIsActive() const {
    return isActive; // Return whether the text box is active
}

std::string TextBox::getInputText() const {
    return inputText; // Return the current input text
}

void TextBox::setInputText(const std::string& text) {
    inputText = text; // Set the input text
    this->text.setString(inputText); // Update the displayed text
}

void TextBox::setPosition(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x + 5, y + 5); // Adjust text position with padding
}

void TextBox::setSize(float width, float height) {
    box.setSize(sf::Vector2f(width, height));
    //text.setCharacterSize(static_cast<unsigned int>(height * 0.6f)); // Adjust text size based on box height
    text.setPosition(box.getPosition().x + 5, box.getPosition().y + 5); // Adjust text position with padding
}

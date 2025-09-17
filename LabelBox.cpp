//
// Created by dawud on 27/07/2025.
//

#include "LabelBox.h"

#include "FontManager.h"

LabelBox::LabelBox(std::string textString, float x, float y, float width, float height, const sf::Color &boxColor) {
    // Initialize the background rectangle
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(boxColor);

    // Initialize the text

    text.setFont(getSharedFont()); // Use a shared font from FontManager
    text.setString(textString);
    text.setCharacterSize(24); // Set a default character size
    text.setFillColor(sf::Color::Black); // Set text color to black
    text.setPosition(x + 10, y + 10); // Add some padding
}

LabelBox::LabelBox() {
    // Default constructor initializes an empty text box
    background.setSize(sf::Vector2f(200, 50)); // Default size
    background.setFillColor(sf::Color(220, 220, 220)); // Default color
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setFont(getSharedFont()); // Use a shared font from FontManager
}

void LabelBox::setText(const std::string &textString) {
    std::istringstream iss(textString);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    std::string currentLine;
    std::string finalText;

    for (const auto& currentWord : words) {
        // Tentative line if we add this word
        std::string testLine = currentLine.empty() ? currentWord : currentLine + " " + currentWord;
        text.setString(testLine);

        if (text.getLocalBounds().width > background.getLocalBounds().width) {
            // Too wide -> push current line to final text, start new line
            if (!finalText.empty()) finalText += "\n";
            finalText += currentLine;
            currentLine = currentWord;
        } else {
            currentLine = testLine;
        }
    }

    // Add the last line
    if (!finalText.empty()) finalText += "\n";
    finalText += currentLine;

    text.setString(finalText);
}
void LabelBox::setPosition(float x, float y) {
    background.setPosition(x, y);
    text.setPosition(x + 10, y + 10); // Adjust text position with padding
}

void LabelBox::setSize(float width, float height) {
    background.setSize(sf::Vector2f(width, height));
}

void LabelBox::setFillColor(const sf::Color &color) {
    background.setFillColor(color);
}

void LabelBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background, states); // Draw the background rectangle
    target.draw(text, states); // Draw the text
}

sf::Vector2f LabelBox::getPosition() const {
    return background.getPosition();
}

sf::Vector2f LabelBox::getSize() const {
    return background.getSize();
}

sf::Text LabelBox::getText() const {
    return text;
}

void LabelBox::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
}


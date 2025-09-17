//
// Created by dawud on 27/07/2025.
//

#ifndef LABELBOX_H
#define LABELBOX_H
#include "SFML/Graphics.hpp"
#include <sstream>
#include <vector>
#include <string>


class LabelBox {
private:
    sf::RectangleShape background; // Background rectangle for the text box
    sf::Text text; // Text to be displayed in the text box
public:
    LabelBox(std::string textString, float x, float y, float width, float height, const sf::Color &boxColor);
    LabelBox(); // Default constructor
    void setText(const std::string &textString); // Set the text in the text box
    void setPosition(float x, float y); // Set the position of the text box
    void setSize(float width, float height); // Set the size of the text box
    void setFillColor(const sf::Color &color); // Set the fill color of the text box
    void draw(sf::RenderTarget &target, sf::RenderStates states) const; // Draw the text box
    sf::Vector2f getPosition() const; // Get the position of the text box
    sf::Vector2f getSize() const; // Get the size of the text box
    sf::Text getText() const; // Get the text in the text box
    void setCharacterSize(unsigned int size); // Set the character size of the text
};



#endif //LABELBOX_H

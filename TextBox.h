//
// Created by dawud on 29/07/2025.
//

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "SFML/Graphics.hpp"
#include "LabelBox.h"

class TextBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    LabelBox labelBox; // Label box for displaying text
    sf::Font font;
    bool isActive;
    std::string inputText;
public:
    TextBox(float x, float y, float width, float height, const sf::Color& color);
    TextBox(); // Default constructor
    bool isClicked(const sf::Vector2f& mousePosition);
    void handleInput(const sf::Event& event);
    void draw(sf::RenderWindow& window, const sf::RenderStates &states) const;
    bool getIsActive() const ;
    std::string getInputText() const;
    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setInputText(const std::string& text);
};



#endif //TEXTBOX_H

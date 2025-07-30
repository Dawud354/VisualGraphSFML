//
// Created by dawud on 21/07/2025.
//

#ifndef USERINTERACTIONBOX_H
#define USERINTERACTIONBOX_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <unordered_map>
#include "button.h"
#include "UserInteractionMessages.h"
#include "LabelBox.h"
#include "TextBox.h"


class UserInteractionBox {
private:
    std::unordered_map<std::string, Button> buttons; // Map to store buttons
    UserInteractionMessages currentMessage; // Current message type
    sf::RectangleShape background; // Background for the box
    sf::RectangleShape nodeDescriptionBox; // Box for node description
    TextBox nodeNameTextBox; // Text box for node name input
    LabelBox neighboursText; // Text box for node neighbours input
    LabelBox nodeNameText; // Label for node name
    LabelBox instructionsBox; // Box for instructions
    std::string oldCircleName; // Store the old circle name for text input
    void addCircle();
    void removeCircle();
    void connectNodes();
    void disconnectNodes();
public:

    UserInteractionBox(float x, float y, float width, float height, const sf::Color& boxColor);
    void draw(sf::RenderWindow &target, sf::RenderStates states) const;
    void handleButtonClick(sf::RenderWindow& window);
    void handleTextInput(sf::Event Event);
    UserInteractionMessages getCurrentMessage() const ;
    void goIntoDragMode();
    void disableRemoveCircle();
    void disableConnectNodes();
    void disableDisconnectNodes();
    void enableRemoveCircle();
    void enableConnectNodes();
    void enableDisconnectNodes();
    void setNodeDescription(const std::string& nodeName,const std::vector<std::string>& neighbours);
    std::vector<std::string> getTextBoxInput();

};



#endif //USERINTERACTIONBOX_H

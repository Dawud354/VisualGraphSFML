//
// Created by dawud on 26/07/2025.
//

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <circle_node.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <circle_node_box.h>

#include "button.h"
#include "UserInteractionBox.h"
#include "circle_node_box_messages.h"

class MainFrame {
private:
    sf::RenderWindow window;
    CircleNodeBox circleBox;
    UserInteractionBox userInteractionBox;
    void handleMouseClick();
    void handleMouseRelease();
public:
    MainFrame();
    void run();
};



#endif //MAINFRAME_H

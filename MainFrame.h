//
// Created by dawud on 26/07/2025.
//

#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <CircleNode.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <CircleNodeBox.h>

#include "Button.h"
#include "UserInteractionBox.h"
#include "CircleNodeBoxMessages.h"

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

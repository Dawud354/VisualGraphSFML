//
// Created by dawud on 26/07/2025.
//

#include "MainFrame.h"

MainFrame::MainFrame(): window(sf::VideoMode(1280, 720), "SFML Window", sf::Style::Titlebar | sf::Style::Close),circleBox(500, 10, 760, 700, sf::Color(200, 200, 200)), userInteractionBox(10, 10, 480, 700, sf::Color(200, 200, 200)) {
    // Create a window with the title "SFML Window"
    //sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Window", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60); // Cap to 60 FPS
    }

void MainFrame::run() {
    bool mouseClicked = false;


    // Main loop that continues until the window is closed
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            // Close window if the close event is triggered
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(); // Handle mouse click
            }

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                handleMouseRelease(); // Handle mouse release
            }

            // will only update circle positions if the left mouse button is held down
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                circleBox.updateCirclePositions(window);
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                std::vector<std::string> input = userInteractionBox.getTextBoxInput(); // Get input from the text box
                circleBox.updateCircleName(input[0],input[1]); // Update the circle name with the input from the text box
            }

            if (event.type == sf::Event::TextEntered) {
                userInteractionBox.handleTextInput(event); // Handle text input in the user interaction box
            }


        }


        // Clear the window with black color
        window.clear(sf::Color::White);

        //window.draw(circle); // Draw the circle

        if (circleBox.canRemoveCircle()) {
            userInteractionBox.enableRemoveCircle();
        }
        else {
            userInteractionBox.disableRemoveCircle();
        }
        if (circleBox.canConnectOrDisconnectCircles()) {
            userInteractionBox.enableConnectNodes();
            userInteractionBox.enableDisconnectNodes();
        }
        else {
            userInteractionBox.disableConnectNodes();
            userInteractionBox.disableDisconnectNodes();
        }


        circleBox.draw(window, sf::RenderStates::Default); // Draw the circles in the box
        userInteractionBox.draw(window, sf::RenderStates::Default); // Draw the user interaction box
        // Display the contents of the window
        window.display();

    }
}

void MainFrame::handleMouseClick() {
    this->userInteractionBox.handleButtonClick(window); // Handle button clicks in the user interaction box
    UserInteractionMessages messages = userInteractionBox.getCurrentMessage();
    switch (messages) {
        case UserInteractionMessages::ADD_CIRCLE:
            std::cout << "Adding circle" << std::endl;
            circleBox.addCircle(50, sf::Color::Blue); // Add a new circle with radius 50 and blue color
            break;
        case UserInteractionMessages::REMOVE_CIRCLE:
            std::cout << "Deleting circle" << std::endl;
            circleBox.setIsDeleting(true); // Set the delete mode to true
            circleBox.removeCircle(window); // Remove circle if in delete mode
            break;
        case UserInteractionMessages::CONNECT_CIRCLES:
            std::cout << "Connecting nodes" << std::endl;
            circleBox.connectCircles(window); // Connect circles if in connect mode
            break;
        case UserInteractionMessages::DISCONNECT_CIRCLES:
            std::cout << "Disconnecting nodes" << std::endl;
            circleBox.disconnectCircles(window); // Disconnect circles if in disconnect mode
            break;
        case UserInteractionMessages::DRAG_CIRCLE: {
            circleBox.updateCirclePositions(window); // Ensure delete mode is off when dragging
            std::string currentCircle = circleBox.getCurrentCircle(); // Get the current circle being interacted with
            const std::vector<std::string> neighbours = circleBox.getCircleNeighbours(currentCircle);
            userInteractionBox.setNodeDescription(currentCircle,neighbours);
            std::cout << "Dragging circle" << std::endl;
            }
        default:
            break;
    }
}

void MainFrame::handleMouseRelease() {
    // Handle mouse release events if needed
    std::cout << "Mouse released" << std::endl;
    // Reset any flags or states if necessary
    CircleNodeBoxMessages messages = circleBox.getCurrentMessage();
    std::cout << "Current message: " << to_string(messages) << std::endl;
    if (userInteractionBox.getCurrentMessage() == UserInteractionMessages::EDIT_CIRCLE_NAME) {
        return; // do not go into drag mode
    }
    if (!(messages == CircleNodeBoxMessages::SELECTED_ONE_CIRCLE_TO_DISCONNECT || messages == CircleNodeBoxMessages::SELECTED_ONE_CIRCLE_TO_CONNECT) && messages != CircleNodeBoxMessages::NOTHING_DONE) {
        userInteractionBox.goIntoDragMode(); // Go into drag mode after a mouse release
        std::cout << "Going into drag mode" << std::endl<< std::endl;
    }
}

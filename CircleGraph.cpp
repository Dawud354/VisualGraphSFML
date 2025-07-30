//
// Created by dawud on 24/07/2025.
//

#include "CircleGraph.h"
#include "line.h"
#include <iostream>
#include <ranges>

void CircleGraph::addCircle(const std::string &label, float radius, const sf::Color &color, int x, int y) {
    if (graph.getNodeCount()>=15) {
        std::cout << "Cannot add more than 15 circles." << std::endl; // Limit the number of circles to 15
        return;
    }
    graph.addNode(label); // Add the node to the graph
    CircleNode circle(radius, color);
    circle.setPosition(x,y); // Set the position of the CircleNode
    circles.emplace(label, circle); // Associate the label with the CircleNode
    std::cout << graph.toString() << std::endl; // Print the graph structure
}

int CircleGraph::getCircleCount() const {
    return graph.getNodeCount(); // Return the number of nodes in the graph
}

void CircleGraph::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto &[label, circle] : circles) {
        circle.draw(target, states); // Draw each CircleNode
        std::vector<std::string> edges= graph.getEdges(label);
        for (const auto &edge : edges) {
            CircleNode neighbour = circles.find(edge)->second;
            Line line(circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius()),
                     neighbour.getPosition() + sf::Vector2f(neighbour.getRadius(), neighbour.getRadius()),
                     sf::Color::Black, 10.0f); // Create a line between the circles
            line.draw(target); // Draw the line
            }
        }
    }




std::vector<std::string> CircleGraph::getCircles() const {
    std::vector<std::string> circleList;
    for (const auto &[label, circle] : circles) {
        circleList.push_back(label); // Collect all CircleNodes into a vector
    }
    return circleList;
}

void CircleGraph::setCirclePosition(const std::string &label, float x, float y) {
    auto it = circles.find(label);
    if (it != circles.end()) {
        it->second.setPosition(x, y); // Set the position of the CircleNode with the given label
    } else {
        std::cerr << "Circle with label " << label << " not found." << std::endl; // Error handling if label not found
    }
}

sf::Vector2f CircleGraph::getCirclePosition(const std::string &label) const {
    auto it = circles.find(label);
    if (it != circles.end()) {
        return it->second.getPosition(); // Return the position of the CircleNode with the given label
    } else {
        std::cerr << "Circle with label " << label << " not found." << std::endl; // Error handling if label not found
        return {0, 0}; // Return a default position if not found
    }
}

float CircleGraph::getCircleRadius(const std::string &label) const {
    auto it = circles.find(label);
    if (it != circles.end()) {
        return it->second.getRadius(); // Return the radius of the CircleNode with the given label
    } else {
        std::cerr << "Circle with label " << label << " not found." << std::endl; // Error handling if label not found
        return 0; // Return a default radius if not found
    }
}

void CircleGraph::removeCircle(const std::string &label) {
    graph.removeNode(label); // Remove the node from the graph
    circles.erase(label); // Remove the CircleNode from the map

}

void CircleGraph::addEdge(const std::string &label1, const std::string &label2) {
    graph.addEdge(label1, label2); // Add an edge between two nodes in the graph
    graph.addEdge(label2, label1); // Ensure the edge is bidirectional
    std::cout <<"\n" <<graph.toString() << std::endl; // Print the graph structure after adding the edge
}

void CircleGraph::removeEdge(const std::string &label1, const std::string &label2) {
    graph.removeEdge(label1, label2); // Remove the edge between two nodes in the graph
    graph.removeEdge(label2, label1); // Ensure the edge is removed bidirectionally
}

std::vector<std::string> CircleGraph::getCircleNeighbours(const std::string &label) const {
    return graph.getEdges(label); // Return the neighbours of the CircleNode with the given label
}

void CircleGraph::changeCircleLabel(const std::string &oldLabel, const std::string &newLabel) {
    if (oldLabel == newLabel) {
        return; // No change needed if labels are the same
    }
    if (circles.find(newLabel) != circles.end()) {
        std::cerr << "Circle with label " << newLabel << " already exists." << std::endl; // Error handling if new label already exists
        return;
    }
    auto it = circles.find(oldLabel);
    if (it != circles.end()) {
        CircleNode circle = it->second; // Get the CircleNode
        circles.erase(it); // Remove the old label
        circles.emplace(newLabel, circle); // Add the CircleNode with the new label
        graph.updateNodeLabel(oldLabel, newLabel); // Update the label in the graph
    }
}
//
// Created by dawud on 24/07/2025.
//

#ifndef CIRCLEGRAPH_H
#define CIRCLEGRAPH_H
#include "Graph.h"
#include <vector>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include "CircleNode.h"


class CircleGraph {
private:
    Graph graph; // The underlying graph structure
    std::unordered_map<std::string, CircleNode> circles; // Map to associate labels with CircleNodes
public:
    CircleGraph() = default;
    void addCircle(const std::string &label, float radius, const sf::Color &color, int x, int y);
    std::vector<std::string> getCircles() const;
    std::vector<std::string> getCircleNeighbours(const std::string &label) const;
    int getCircleCount() const;
    void draw (sf::RenderTarget &target, sf::RenderStates states) const;
    void setCirclePosition(const std::string &label, float x, float y);
    sf::Vector2f getCirclePosition(const std::string &label) const;
    float getCircleRadius(const std::string &label) const;
    void removeCircle(const std::string &label);
    void addEdge(const std::string &label1, const std::string &label2);
    void removeEdge(const std::string &label1, const std::string &label2);
    void changeCircleLabel(const std::string &oldLabel, const std::string &newLabel) ;

};



#endif //CIRCLEGRAPH_H

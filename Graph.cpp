//
// Created by dawud on 07/01/2025.
//

#include "Graph.h"

#include <iostream>
#include <stdexcept>
#include<algorithm>
#include <queue>
#include <set>
#include <stack>


Graph::Node::Node(std::string label) : label(std::move(label)) {}

void Graph::addNode(const std::string &label) {
    Node node = Node(label);
    std::shared_ptr<Node> nodePtr = std::make_shared<Node>(node);
    nodes.emplace(label, nodePtr);
    adjacencyList.emplace(nodePtr, std::vector<std::shared_ptr<Node>>{});
}

void Graph::removeNode(const std::string &label) {
    if (!nodes.contains(label)) {
        return;
    }
    const std::shared_ptr<Node> nodePtr = nodes[label];
    for (auto &[key, neighbors] : adjacencyList) {
        neighbors.erase(std::ranges::remove(neighbors, nodePtr).begin(), neighbors.end());
    }
    adjacencyList.erase(nodePtr);
    nodes.erase(label);
}

void Graph::addEdge(const std::string &from, const std::string &to) {
    std::cout << toString() << std::endl;
    if (!nodes.contains(from) || !nodes.contains(to)) {
        throw std::invalid_argument("Both nodes must exist");
    }
    const std::shared_ptr<Node> nodeFrom = nodes[from];
    const std::shared_ptr<Node> nodeTo = nodes[to];
    std::vector<std::shared_ptr<Node>> &neighbors = adjacencyList[nodeFrom];
    //if the node is already in the vector of neighbors, return
    if (std::ranges::find(neighbors, nodeTo) != neighbors.end()) {
        return;
    }
    adjacencyList[nodeFrom].push_back(nodeTo);
}

void Graph::removeEdge(const std::string &from, const std::string &to) {
    if (!nodes.contains(from) || !nodes.contains(to)) {
        return;
    }
    if (from == to) {
        return; // Cannot remove self-loop
    }
    const std::shared_ptr<Node> nodeFrom = nodes[from];
    const std::shared_ptr<Node> nodeTo = nodes[to];
    std::vector<std::shared_ptr<Node>> &neighbors = adjacencyList[nodeFrom];
    //find node and the remove it.
    // I used find instead of remove because there is only one instance of the node in the vector
    auto it = std::find(neighbors.begin(), neighbors.end(), nodeTo);
    if (it == neighbors.end()) {
        return; // Node not found in neighbors
    }
    neighbors.erase(it);
}

std::string Graph::toString() {
    std::string result;
    for (const auto &[node, neighbors] : adjacencyList) {
        std::string neighborsStr;
        for (const auto &neighbor : neighbors) {
            neighborsStr += neighbor->getLabel() + ", ";
        }
        //remove the last comma and space
        if (!neighbors.empty()) {
            neighborsStr = neighborsStr.substr(0, neighborsStr.length() - 2);
        }
        else {
            neighborsStr="none";
        }
        result += node->getLabel() + " -> " + neighborsStr + "\n";
    }
    if (result.empty()) {
        return "Graph is empty";
    }
    return result;

}

// will need to fix later
/*
void Graph::depthFirstTraversal(const std::string &root) {
    if (!nodes.contains(root)) {
        return;
    }
    std::set<Node> visited;
    //iterative version
    std::stack<Node> toVisit;
    toVisit.push(nodes[root]);
    while (!toVisit.empty()) {
        Node current = toVisit.top();
        toVisit.pop();
        //if the node has already been visited, skip it
        if (visited.contains(current)) {
            continue;
        }
        std::cout<<current.getLabel()<<std::endl;
        visited.insert(current);
        // adds unvisited neighbors to the stack
        for (const auto &neighbor : adjacencyList[current]) {
            if (!visited.contains(neighbor)) {
                toVisit.push(neighbor);
            }
        }
    }


    // recursive version
    //depthFirstTraversal(nodes[root], visited);
}

void Graph::depthFirstTraversal(const Node &node, std::set<Node> &visited) {
    if (visited.contains(node)) {
        return;
    }
    std::cout << node.getLabel() << std::endl;
    visited.insert(node);
    for (const auto &neighbor : adjacencyList[node]) {
        if (!visited.contains(neighbor)) {
            depthFirstTraversal(neighbor, visited);
        }
    }
}

void Graph::breadthFirstTraversal(const std::string &root) {
    if (!nodes.contains(root)) {
        return;
    }
    std::set<Node> visited;
    //iterative version
    std::queue<Node> toVisit;
    toVisit.push(nodes[root]);
    while (!toVisit.empty()) {
        Node current = toVisit.front();
        toVisit.pop();
        //if the node has already been visited, skip it
        if (visited.contains(current)) {
            continue;
        }
        std::cout<<current.getLabel()<<std::endl;
        visited.insert(current);
        // adds unvisited neighbors to the queue
        for (const auto &neighbor : adjacencyList[current]) {
            if (!visited.contains(neighbor)) {
                toVisit.push(neighbor);
            }
        }
    }
}

std::vector<std::string> Graph::topologicalSort() {
    std::stack<Node> sorted;
    std::set<Node> visited;
    for (const auto &[node, _] : adjacencyList) {
        if (!visited.contains(node)) {
            topologicalSort(node, visited, sorted);
        }
    }
    std::vector<std::string> result;
    while (!sorted.empty()) {
        result.push_back(sorted.top().getLabel());
        sorted.pop();
    }
    return result;
}

void Graph::topologicalSort(const Node &root, std::set<Node> &visited, std::stack<Node> &sorted) {
    if (!visited.contains(root)) {
        return;
    }
    visited.insert(root);
    for (const auto &neighbor : adjacencyList[root]) {
        if (!visited.contains(neighbor)) {
            topologicalSort(neighbor, visited, sorted);
        }
    }
    sorted.push(root);
}

bool Graph::Graph::hasCycle() {
    std::set<Node> all;
    for (const auto &[node, _] : adjacencyList) {
        all.insert(node);
    }
    std::set<Node> visiting;
    std::set<Node> visited;
    for (const auto &node : all) {
        if (hasCycle(node, visiting, visited)) {
            return true;
        }
    }
    return false;
}

bool Graph::hasCycle(const Node &node, std::set<Node> &visiting, std::set<Node> &visited) {
    if (visited.contains(node)) {
        return false;
    }
    if (visiting.contains(node)) {
        return true;
    }
    visiting.insert(node);
    for (const auto &neighbor : adjacencyList[node]) {
        if (hasCycle(neighbor, visiting, visited)) {
            return true;
        }
    }
    visiting.erase(node);
    visited.insert(node);
    return false;

}
*/
int Graph::getNodeCount() const {
    return nodes.size();
}


std::string Graph::Node::getLabel() const {
    return label;
}

std::vector<std::string> Graph::getEdges(const std::string& node) const {
    std::vector<std::string> edges;
    if (!nodes.contains(node)) {
        return edges; // Return empty vector if node does not exist
    }
    for (const auto &neighbor : adjacencyList.at(nodes.at(node))) {
        edges.push_back(neighbor->getLabel());
    }
    return edges;
}

void Graph::updateNodeLabel(const std::string &oldLabel, const std::string &newLabel) {
    std::cout << "Updating label from " << oldLabel << " to " << newLabel << std::endl;
    if (oldLabel == newLabel) {
        return; // No change needed if labels are the same
    }
    if (!nodes.contains(oldLabel)) {
        throw std::invalid_argument("Node with label " + oldLabel + " does not exist.");
    }
    if (nodes.contains(newLabel)) {
        throw std::invalid_argument("Node with label " + newLabel + " already exists.");
    }
    auto it = nodes.find(oldLabel);
    if (it != nodes.end()) {
        std::cout << "Node with label " << oldLabel << "found." << std::endl;
        std::shared_ptr<Node> node = it->second;
        node->setLabel(newLabel); // update the label of the node
        nodes.erase(oldLabel); // remove the old label from the map
        nodes.emplace(newLabel, node); // add the node with the new label
    }
}



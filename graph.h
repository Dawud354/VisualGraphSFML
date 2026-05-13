//
// Created by dawud on 07/01/2025.
//

#ifndef GRAPH_H
#define GRAPH_H
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <set>
#include <stack>
#include <memory>

class Graph {
private:
    class Node {
        std::string label;
    public:
        explicit Node(std::string label);
        Node() = default;

        std::string getLabel() const;
        bool operator==(const Node &rhs) const {
            return label == rhs.label;
        }
        void setLabel(const std::string &newLabel) {
            label = newLabel;
        }
        bool operator<(const Node &rhs) const {
            return label < rhs.label;
        }
    };
    // struct NodeHash {
    //     std::size_t operator()(const Node &node) const {
    //         return std::hash<std::string>()(node.getLabel());
    //     }
    // };
    std::unordered_map<std::string,std::shared_ptr<Node>> nodes;
    std::unordered_map<std::shared_ptr<Node>,std::vector<std::shared_ptr<Node>>> adjacencyList;
    void depthFirstTraversal(const Node &node, std::set<Node> &visited);
    void topologicalSort(const Node &root, std::set<Node> &visited, std::stack<Node> &sorted);
    bool hasCycle(const Node &node, std::set<Node> &visiting, std::set<Node> &visited);
public:
    void addNode(const std::string &label);
    void removeNode(const std::string &label);
    void addEdge(const std::string &from, const std::string &to);
    void removeEdge(const std::string &from, const std::string &to);
    void depthFirstTraversal(const std::string &root);
    void breadthFirstTraversal(const std::string &root);
    std::vector<std::string> topologicalSort();
    bool hasCycle();
    std::string toString();
    int getNodeCount() const;
    std::vector<std::string> getEdges(const std::string& node) const;
    void updateNodeLabel(const std::string &oldLabel, const std::string &newLabel);
};



#endif //GRAPH_H

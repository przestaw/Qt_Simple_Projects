#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"

class Graph : public QObject
{
    Q_OBJECT
public:
    Graph();
    ~Graph();
    bool checkNodeName(std::string name);
    /**
     * @brief addEdge adds edge to the graph if node one and two exist in the graph
     * @param one Node of the edge
     * @param two Node of the edge
     */
    void addEdgeByNodes(Node *one, Node *two);
public slots:
    /**
     * @brief removeEdge removes edge from graph if edge with that Nodes exists
     * @param one Node of the edge
     * @param two Node of the edge
     */
    void removeEdgeByNodes(Node *one, Node *two);
    /**
     * @brief removeEdge removes edge from graph if this edge exist
     * @param edge Edge to be removed
     */
    void removeEdge(Edge *edge);
    /**
     * @brief removeEdges remove all edges with given node
     * @param node Node thats edges will be removed
     */
    void removeEdges(Node *node);
    /**
     * @brief removeNode removes Node from graph, also removing all edges connected to the node
     * @param node node to be removed
     */
    void removeNode(Node *node);

    /**
     * @brief addNode adds Nodes to the graph
     * @param node node to be addes
     */
    void addNode(Node *node);
    /**
     * @brief addEdge adds edge to the graph if its nodes belong to the graph
     * @param edge edge to be added to graph
     */
    void addEdge(Edge *edge);

    void eraseContents();
signals:
    /**
     * @brief createdEdge triggerd to allow newly created edge to be displayed
     * @param edge edge created and allocated in graph
     */
    void createdEdge(Edge* edge);
    /**
     * @brief createdNode
     * @param node
     */
    void createdNode(Node* node);

private:
//    inline bool isNodeInGraph (Node& node){
//        return 0 != std::count_if(nodes.begin(),nodes.end(),
//                                   [&node](  Node& other){return false/*node.getName() == other.getName()*/;});
//    }
    void clearGraph();
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;
};

#endif // GRAPH_H

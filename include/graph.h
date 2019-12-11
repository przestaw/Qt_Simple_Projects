#ifndef GRAPH_H
#define GRAPH_H

#include "node.h"
#include "edge.h"
#include <memory>

class Graph : public QGraphicsScene{
    Q_OBJECT
public:
    Graph();
    ~Graph();

    inline bool isCityInGraph (QString name){
        return 0 != std::count_if(nodes.begin(),nodes.end(),
                                   [name](Node* other){return name == other->getName();});
    }

    inline bool isNodeInGraph (Node* node){
        return 0 != std::count_if(nodes.begin(),nodes.end(),
                                   [node](Node* other){return node == other;});
    }

    inline bool isEdgeInGraph (QString one, QString two){
        return 0 != std::count_if(edges.begin(),edges.end(),
                                   [one, two](Edge* edge){return edge->connectsCity(one) && edge->connectsCity(two);});
    }

    inline bool isEdgeInGraph (Node* one, Node* two){
        return 0 != std::count_if(edges.begin(),edges.end(),
                                   [one, two](Edge* edge){return edge->hasNode(one) && edge->hasNode(two);});
    }

    inline bool isEdgeInGraph (Edge* edge){
        return 0 != std::count_if(edges.begin(),edges.end(),
                                   [edge](Edge* other){return *edge == *other;});
    }

    /**
     * @brief addEdge adds edge to the graph if node one and two exist in the graph
     * @param one Node of the edge
     * @param two Node of the edge
     */
    void addEdgeByNodes(Node *one, Node *two);
public slots:
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

public:

    void clearGraph();
private:

    std::vector<Node*> nodes;
    std::vector<Edge*> edges;
};

#endif // GRAPH_H

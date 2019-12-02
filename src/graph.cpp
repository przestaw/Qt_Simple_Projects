#include "graph.h"


#include <QDebug>

Graph::Graph(){}

Graph::~Graph(){
    clearGraph();
}

void Graph::clearGraph(){
    std::for_each(edges.begin(), edges.end(), [](Edge *edge){ delete edge;});
    std::for_each(nodes.begin(), nodes.end(), [](Node *node){ delete node;});
}

void Graph::removeEdgeByNodes(Node *one, Node *two){
    Q_UNUSED(one)
    Q_UNUSED(two)
    //TODO
}

void Graph::removeEdge(Edge *edge){
    edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
    delete edge;
}

void Graph::removeEdges(Node *node){
    auto begin = std::remove_if(edges.begin(), edges.end(), [node](Edge *edge){ return edge->hasNode(node);});
    std::for_each(begin, edges.end(), [](Edge *edge){ delete edge;});
    edges.erase(begin, edges.end());
}

void Graph::removeNode(Node *node){
    this->removeEdges(node);
    nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
    auto scene = node->scene();
    delete node;
    scene->invalidate();// to avoid artifacts after node deletion

//    auto toDelete = std::find_if(nodes.begin(),nodes.end(), [node](Node *other){return node == other;});
//    if(toDelete !=nodes.end()){
//        nodes.erase(toDelete);
//    }
}

void Graph::addNode(Node *node){
    nodes.push_back(node);
    emit createdNode(node);
}

void Graph::addEdge(Edge *edge){
    //TODO avoid adding duplicates
    edges.push_back(edge);
    emit createdEdge(edge);
}

void Graph::eraseContents(){
    this->clearGraph();
}

void Graph::addEdgeByNodes(Node *one, Node *two){
    //TODO chech if edge exists
    Edge *edge = new Edge(one, two);
    edges.push_back(edge);
    emit createdEdge(edge);
}

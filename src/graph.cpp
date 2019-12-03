#include "graph.h"
#include <QDebug>
#include <algorithm>

Graph::Graph(){}

Graph::~Graph(){
    clearGraph();
}

void Graph::clearGraph(){
    std::for_each(edges.begin(), edges.end(), [](Edge *edge){ delete edge;});
    std::for_each(nodes.begin(), nodes.end(), [](Node *node){ delete node;});
    edges.erase(edges.begin(), edges.end());
    nodes.erase(nodes.begin(), nodes.end());
}

void Graph::removeEdge(Edge *edge){
    edges.erase(std::remove(edges.begin(), edges.end(), edge), edges.end());
    delete edge;
}

void Graph::removeEdges(Node *node){
//    auto begin = std::remove_if(edges.begin(), edges.end(),
//            [node](Edge *edge){ return edge->connectsCity(node->getName());});
//    std::for_each(begin, edges.end(), [](Edge *edge){ delete edge;});
//    edges.erase(begin, edges.end());
    // void* T* are not move-assignable

    for(long long int i = edges.size() - 1; i >= 0; --i){
        if(edges[i]->hasNode(node)){
            delete edges[i];
            edges.erase(edges.begin() + i);
        }
    }
}

void Graph::removeNode(Node *node){
    auto scene = node->scene();
    this->removeEdges(node);
    delete node;
    nodes.erase(std::remove(nodes.begin(), nodes.end(), node), nodes.end());
    scene->invalidate();// to avoid artifacts after node deletion //TODO : Signal?
}

void Graph::addNode(Node *node){
    if(!this->isCityInGraph(node->getName())){
        nodes.push_back(node);
        emit createdNode(node);
    } else {
        delete node;
    }
}

void Graph::addEdge(Edge *edge){
    if(!isEdgeInGraph(edge)){
        edges.push_back(edge);
        emit createdEdge(edge);
    } else {
        delete edge;
    }
}

void Graph::eraseContents(){
    this->clearGraph();
}

void Graph::addEdgeByNodes(Node *one, Node *two){
    if(!isEdgeInGraph(one, two) && isNodeInGraph(one) && isNodeInGraph(two)){
        Edge *edge = new Edge(one, two);
        edges.push_back(edge);
        emit createdEdge(edge);
    }
}

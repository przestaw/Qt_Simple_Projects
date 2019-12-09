#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include "edge.h"
#include "node.h"

class GraphView : public QGraphicsView{
    Q_OBJECT
public:
    GraphView(QWidget *parent = nullptr);

public slots:
    void addEdgeToScene(Edge *edge);
    void addNodeToScene(Node *node);
    void invalidateScene();
signals:
    void addEdge(Edge* edge);
    void addNode(Node* node);
    void removeNode(Node* node);
    void removeEdge(Edge* edge);
    void removeEdges(Node* node);

    void renameNode(Node* node);
    void changeDist(Edge* edge);
    void createNode(QPointF pos);

    void nodePosChanged(Node* node); //TODO
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Node* arcFrom;
    bool isArcCreated;
};

#endif // GRAPHVIEW_H

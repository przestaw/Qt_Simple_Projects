#ifndef GRAPHVIEW_H
#define GRAPHVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMouseEvent>
#include "edge.h"
#include "node.h"
#include <QSvgRenderer>

class GraphView : public QGraphicsView{
    Q_OBJECT
public:
    GraphView(QWidget *parent = nullptr);
signals:
    void renameNode(Node* node);
    void changeDist(Edge* edge);
    void createNode(QPointF pos);
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void drawBackground(QPainter *painter, const QRectF &rect);
private:
    QSvgRenderer rend;
    Node* arcFrom;
    bool isArcCreated;  
    QRectF rectSpace;
};

#endif // GRAPHVIEW_H

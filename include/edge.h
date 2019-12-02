#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include "node.h"

class Edge : public QGraphicsItem
{
public:
    Edge(Node *one, Node *two, double distance);
    Edge(Node *one, Node *two);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    double getDistance();
    void setDistance(double newDistance);
    void autoCalcDistance();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

    bool hasNode(Node *node);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
private:
    Node *one;
    Node *two;
    double distance;
};

#endif // EDGE_H

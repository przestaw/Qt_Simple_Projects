#ifndef GRAPHICNODE_H
#define GRAPHICNODE_H

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QGraphicsView>
#include <QGraphicsItem>

class Node : public QGraphicsItem{
public:
    Node(QString name);
    Node(QPointF pos, QString name);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    QString getName();
    void setName(QString name);
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

private:
    bool isMoving;
    QString name;
    QFont font;

    static const QColor selectedColor;
    static const QColor standardColor;
    static const QColor borderColor;
    static const int nodeRadius;
};

#endif // GRAPHICNODE_H

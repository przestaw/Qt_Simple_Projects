#ifndef COORDINATESGRID_H
#define COORDINATESGRID_H

#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPicture>

class CoordinatesGrid : public QGraphicsItem {
public:
    CoordinatesGrid();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    enum { Type = UserType + 3 };
    int type() const override { return Type; }
private:
    QPicture worldMap;
};

#endif // COORDINATESGRID_H

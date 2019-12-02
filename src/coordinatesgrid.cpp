#include "coordinatesgrid.h"

#include <QDebug>

CoordinatesGrid::CoordinatesGrid(){
    setPos(0,0);
    this->setZValue(-5);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    //qDebug() << worldMap.load(":/world.svg");
}

void CoordinatesGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    //painter->drawPicture(0, 0, worldMap);

    painter->setPen(QPen(Qt::GlobalColor::lightGray, 0.3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    QVector<QLineF> lines;
    for(int i = -90; i <= 90; i+=10){
        lines.push_back(QLineF(180, i, -180, i));
    }
    for(int i = -180; i <= 180; i+=10){
        lines.push_back(QLineF( i, -90, i, 90));
    }
    painter->drawLines(lines);
}

QRectF CoordinatesGrid::boundingRect() const{
    return QRectF(-180, -90, 360, 180);
}

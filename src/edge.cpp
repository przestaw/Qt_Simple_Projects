#include "edge.h"
#include <QtMath>

Edge::Edge(Node *one, Node *two, double distance) : one(one), two(two), distance(distance){
    this->setZValue(-1);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
}

Edge::Edge(Node *one, Node *two) : one(one), two(two){
    this->setZValue(-1);
    this->autoCalcDistance();
}

QRectF Edge::boundingRect() const{
    return QRectF(one->pos(), two->pos()).normalized();
}

QPainterPath Edge::shape() const{
    QPainterPath path;
    QPolygonF polygon;
    QRectF bounding = this->boundingRect(); //to reuse code and avoid multiple calls

    polygon << bounding.topLeft() + QPointF(0, 3);
    polygon << bounding.topLeft() + QPointF(3, 0);
    polygon << bounding.bottomRight() + QPointF(0, -3);
    polygon << bounding.bottomRight() + QPointF(-3 , 0);

    path.addPolygon(polygon);
    return path;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QLineF line(one->pos(), two->pos());
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;


    painter->setPen(QPen(Qt::red, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    painter->setPen(QPen(Qt::black));
    QFont font; font.setPointSizeF(5);
    painter->setFont(font);
    QString txt = QString().setNum(this->distance, 'g', 5);//std::to_string(this->distance));
    painter->drawText(this->boundingRect().center(), txt);
}

double Edge::getDistance(){
    return this->distance;
}

void Edge::setDistance(double newDistance){
    if(newDistance < 0){
        this->distance = 0;
    } else {
        this->distance = newDistance;
    }
}

void Edge::autoCalcDistance() {
    this->distance = QLineF(one->pos(), two->pos()).length();
}

bool Edge::hasNode(Node *node){
    return one == node || two == node;
}

void Edge::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::hoverEnterEvent(event);
}

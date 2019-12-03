#include "edge.h"
#include <QtMath>

Edge::Edge(Node *one, Node *two, double distance) : one(one), two(two), distance(distance){
    this->setZValue(-1);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
}

Edge::Edge(Node *one, Node *two) : one(one), two(two){
    this->setZValue(-1);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    this->autoCalcDistance();
}

QRectF Edge::boundingRect() const{
    return QRectF(one->pos(), two->pos()).normalized();
}

QPainterPath Edge::shape() const{
    QPainterPath path;
    QPolygonF polygon;
    QLineF line = QLineF(one->pos(), two->pos());
    QPointF center = line.center();
    double lenght = line.length()/2;

    polygon << center + QPointF(-lenght, 2.2);
    polygon << center + QPointF(-lenght, -2.2);
    polygon << center + QPointF(lenght, -2.2);
    polygon << center + QPointF(lenght, 2.2);

    polygon = QTransform()
       .translate(center.x(), center.y())
       .rotate(-line.angle())
       .translate(-center.x(),-center.y())
       .map(polygon);

    path.addPolygon(polygon);
    return path;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QLineF line(one->pos(), two->pos());
    QFont font; font.setPointSizeF(5);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    if(this->isSelected()){
         painter->setPen(QPen(Qt::red, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter->setPen(QPen(Qt::red, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    painter->drawLine(line);
    painter->setPen(QPen(Qt::black));
    painter->setFont(font);
    QString txt = QString().setNum(this->distance, 'g', 5);//std::to_string(this->distance));
    painter->drawText(this->boundingRect().center(), txt);
    //painter->drawPolyline(shape().toFillPolygon());
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
    //this->distance = QLineF(one->pos(), two->pos()).length();
    double latRad1 = qDegreesToRadians(one->pos().y());
    double latRad2 = qDegreesToRadians(two->pos().y());
    double lonRad1 = qDegreesToRadians(one->pos().x());
    double lonRad2 = qDegreesToRadians(two->pos().x());

    double diffLa = latRad2 - latRad1;
    double doffLo = lonRad2 - lonRad1;

    this->distance = 2 * 6372.8 * asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));
}

bool Edge::hasNode(Node *node){
    return (one == node || two == node);
}

bool Edge::connectsCity(QString city){
    return (one->getName() == city || two->getName() == city);
}

bool Edge::operator!=(Edge &other){
    return !(*this == other);
}

bool Edge::operator==(Edge &other){
    return (connectsCity(other.one->getName()) && this->connectsCity(other.two->getName()));
}

void Edge::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::hoverEnterEvent(event);
}

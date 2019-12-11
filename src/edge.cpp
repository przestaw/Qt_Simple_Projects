#include "edge.h"
#include <QtMath>

Edge::Edge(Node *one, Node *two, double distance) : one(one), two(two), distance(distance), font(){
    this->setZValue(-1);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    font.setPointSizeF(5);
}

Edge::Edge(Node *one, Node *two) : one(one), two(two), font(){
    this->setZValue(-1);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    this->autoCalcDistance();
    font.setPointSizeF(5);
}

QRectF Edge::boundingRect() const{
    QRectF text = QFontMetrics(font).boundingRect(
                QString().setNum(this->distance, 'g', 4));
    QRectF bound = QRectF(one->pos(), two->pos()).normalized();
    int margin = text.width();
    //text will always be on top, bottom or left [depending on orientation]
    return QRectF(bound.topLeft()+QPointF(-3,-margin),
                  bound.bottomRight()+QPointF(margin,margin));
}

QPainterPath Edge::shape() const{
    QPainterPath path;
    QPolygonF polygon;
    QLineF line = QLineF(one->pos(), two->pos());
    QPointF center = line.center();
    double lenght = line.length()/2;

    polygon << center + QPointF(lenght, 3);
    polygon << center + QPointF(lenght, -3);
    polygon << center + QPointF(-lenght, -3);
    polygon << center + QPointF(-lenght, 3);


    polygon = QTransform()
       .translate(center.x(), center.y())
       .rotate(-line.angle())
       .translate(-center.x(),-center.y())
       .map(polygon);

    path.addPolygon(polygon);

    QRect text = QFontMetrics(font).boundingRect(
                QString().setNum(this->distance, 'g', 4));
    text.moveBottomLeft(QPoint(line.center().toPoint()));
    path.addRect(text);
    return path;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QLineF line(one->pos(), two->pos());

    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    if(this->isSelected()){
         painter->setPen(QPen(Qt::red, 1.2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    } else {
        painter->setPen(QPen(Qt::red, 0.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }

    painter->drawLine(line);
    painter->setPen(QPen(Qt::black));
    painter->setFont(font);
    QString txt = QString().setNum(this->distance, 'g', 4);
    painter->drawText(QLineF(one->pos(),two->pos()).center(), txt);

//    painter->setPen(QPen(Qt::green, 1.4, Qt::SolidLine));
//    painter->drawPolyline(this->shape().toFillPolygon());
//    painter->setPen(QPen(Qt::blue, 1.4, Qt::SolidLine));
//    painter->drawPolygon(this->boundingRect());
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

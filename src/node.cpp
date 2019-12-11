#include "node.h"

const QColor Node::selectedColor = Qt::GlobalColor::green;
const QColor Node::standardColor = Qt::GlobalColor::yellow;
const QColor Node::borderColor = Qt::GlobalColor::black;
const int Node::nodeRadius = 5;

Node::Node(QPointF pos, QString name): isMoving(false), name(name), font(){
    this->setPos(pos);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    font.setPointSizeF(5);

}

Node::Node(QString name): isMoving(false), name(name), font(){
    this->setPos(0,0);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    font.setPointSizeF(5);
}

void Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    setCursor(Qt::PointingHandCursor);
    QGraphicsItem::hoverEnterEvent(event);
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() >= QApplication::startDragDistance()) {
        isMoving = true;
        setCursor(Qt::ClosedHandCursor);
        QPointF position = event->scenePos();
        if(position.x() > 180) position.setX(180);
        if(position.x() < -180) position.setX(-180);
        if(position.y() > 90) position.setY(90);
        if(position.y() < -90) position.setY(-90);
        setPos(position);
        this->scene()->invalidate(); //because edges may move as well
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if (isMoving) {
        setSelected(false);
        isMoving = false;
    }
    setCursor(Qt::ArrowCursor);
    QGraphicsItem::mouseReleaseEvent(event);
}

QRectF Node::boundingRect() const{
    QRect bound = QFontMetrics(font).boundingRect(name);
    bound.moveTopLeft(QPoint(nodeRadius, -nodeRadius/2));
    return bound.united(QRect(-nodeRadius/2, -nodeRadius/2, nodeRadius, nodeRadius));
}


QPainterPath Node::shape() const {
    QPainterPath path;
    path.addEllipse(-nodeRadius/2, -nodeRadius/2, nodeRadius, nodeRadius);

    QRect text = QFontMetrics(font).boundingRect(name);
    text.moveLeft(nodeRadius/2);
    path.addRect(text);

    return path;
}
QString Node::getName() {
    return name;
}
void Node::setName(QString name){
    this->name = name;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QColor myColor;
    if (isSelected()){
        painter->setPen(QPen(borderColor, 1.1, Qt::SolidLine));
        myColor = selectedColor;
    } else {
        painter->setPen(QPen(borderColor, 0.7, Qt::SolidLine));
        myColor = standardColor;
    }
    painter->setBrush(QBrush(myColor));
    painter->drawEllipse(-nodeRadius/2, -nodeRadius/2, nodeRadius, nodeRadius);

    painter->setFont(font);
    painter->drawText(nodeRadius/2, nodeRadius, this->name);
}

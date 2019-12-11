#include "graphview.h"
#include "node.h"
#include "edge.h"
#include "coordinatesgrid.h"
#include "graph.h"


GraphView::GraphView(QWidget *parent) : QGraphicsView(parent), arcFrom(nullptr), isArcCreated(false), rend(QString(":/world"), this){
    setScene(new Graph());
    scene()->addItem(new CoordinatesGrid());
}

void GraphView::contextMenuEvent(QContextMenuEvent *event){
    for (auto gi: scene()->selectedItems())
        gi->setSelected(false);

    QList<QGraphicsItem*> clickedItems = items(event->pos());
    if (clickedItems.size() != 0) {
        auto item = clickedItems[0];
        item->setSelected(true);

        if(item->type() == Node::Type){
            QMenu menu;
            menu.addAction("&Delete");
            menu.addAction("Re&name");
            menu.addSeparator();
            menu.addAction("&Set road to (Select other city by mouse)");
            menu.addAction("&Izolate node (remove roads)");
            QAction *act = menu.exec(event->globalPos());
            if(act != nullptr){
                if(act->text() == "&Delete"){
                    static_cast<Graph*>(scene())->removeNode(static_cast<Node*>(item));
                } else if(act->text() == "Re&name"){
                    emit renameNode(static_cast<Node*>(item));
                } else if(act->text().contains("&Set road to")){
                    isArcCreated = true;
                    arcFrom = static_cast<Node*>(item);
                } else if(act->text() == "&Izolate node (remove roads)"){
                    static_cast<Graph*>(scene())->removeEdges(static_cast<Node*>(item));
                }
            } else {
                item->setSelected(false);
            }
        } else if(item->type() == Edge::Type){
            QMenu menu;
            menu.addAction("&Delete");
            menu.addAction("&Change/Set Distance");
            menu.addAction("&Auto-Calc Distance");
            QAction *act = menu.exec(event->globalPos());
            if(act != nullptr){
                if(act->text() == "&Delete"){
                    static_cast<Graph*>(scene())->removeEdge(dynamic_cast<Edge*>(item));
                } else if(act->text() == "&Change/Set Distance"){
                    emit changeDist(static_cast<Edge*>(item));
                } else if (act->text() == "&Auto-Calc Distance"){
                    static_cast<Edge*>(item)->autoCalcDistance();
                    this->scene()->invalidate();
                }
            } else {
                item->setSelected(false);
            }
        } else if(item->type() == CoordinatesGrid::Type){
            QMenu menu;
            menu.addAction("&New node here");
            QAction *act = menu.exec(event->globalPos());
            if(act != nullptr){
                if (act->text() == "&New node here"){
                    emit createNode(mapToScene(event->pos()));
                }
            }
        }
    }
}

void GraphView::mousePressEvent(QMouseEvent *event){
    if(isArcCreated){
        QList<QGraphicsItem*> clickedItems = items(event->pos());
        if (clickedItems.size() > 0) {
            if(clickedItems[0]->type() == Node::Type) {
                Node* arcTo = static_cast<Node*>(clickedItems[0]);
                if(arcTo != arcFrom){
                    Edge *edge = new Edge(arcTo, arcFrom);
                    static_cast<Graph*>(scene())->addEdge(edge);
                }
            }
        }
        isArcCreated = false;
        arcFrom = nullptr;
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphView::mouseReleaseEvent(QMouseEvent *event) {
    scene()->invalidate(); //to recalc Edge Rect after draging !!
    QGraphicsView::mouseReleaseEvent(event);
}

void GraphView::resizeEvent(QResizeEvent *event){
    QRectF rect = QRectF(-180, -90, 360, 180); // to acomodate svg
    fitInView(rect, Qt::KeepAspectRatio);
    this->scene()->setSceneRect(rect);
    event->accept();
}

void GraphView::drawBackground(QPainter *painter, const QRectF &rect){
    Q_UNUSED(rect);
    painter->setPen(QPen(Qt::white, 0, Qt::NoPen));
    painter->setBrush(QBrush(Qt::lightGray));
    painter->drawRect(QRectF(-180, -90, 360, 180));
    //rend.render(painter, QRectF(-174, -93, 370.7, 186));
}

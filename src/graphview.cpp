#include "graphview.h"
#include "node.h"
#include "edge.h"
#include "coordinatesgrid.h"


GraphView::GraphView(QWidget *parent) : QGraphicsView(parent), arcFrom(nullptr), isArcCreated(false){
    QGraphicsScene *scene = new QGraphicsScene(this);
    this->setScene(scene);
}

void GraphView::addEdgeToScene(Edge *edge){
    this->scene()->addItem(edge);
}

void GraphView::addNodeToScene(Node *node){
    this->scene()->addItem(node);
}

void GraphView::invalidateScene(){
    this->scene()->invalidate();
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
            QAction *act = menu.exec(event->globalPos());
            if(act != nullptr){
                if(act->text() == "&Delete"){
                    emit removeNode(static_cast<Node*>(item));
                } else if(act->text() == "Re&name"){
                    emit renameNode(static_cast<Node*>(item));
                } else if(act->text().contains("&Set road to")){
                    isArcCreated = true;
                    arcFrom = static_cast<Node*>(item);
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
                    emit removeEdge(dynamic_cast<Edge*>(item));
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
    } else {
        // ??
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
                    emit addEdge(edge);
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
    QRectF rect = QRectF(-180, -90, 360, 180);
    fitInView(rect, Qt::KeepAspectRatio);
    this->scene()->setSceneRect(rect);
    event->accept();
}

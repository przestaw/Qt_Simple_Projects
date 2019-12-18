#ifndef EDGEPROP_H
#define EDGEPROP_H

#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "edge.h"

class EdgeProp : public QVBoxLayout {
    Q_OBJECT
public:
    EdgeProp();
public slots:
    void setActiveEdge(Edge *edge);
private slots:
    void getData();
signals:
    void graphEdited();
private:
    Edge* activeEdge;
    QLabel *label;
    QDoubleSpinBox *distance;
    QPushButton *confirmButton;
};

#endif // EDGEPROP_H

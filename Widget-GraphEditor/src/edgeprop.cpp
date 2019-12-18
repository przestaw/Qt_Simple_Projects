#include "edgeprop.h"
#include <limits>

EdgeProp::EdgeProp()
    : activeEdge(nullptr) {
    label = new QLabel("Distance");
    distance = new QDoubleSpinBox();
    distance->setRange(0, std::numeric_limits<double>::max());
    confirmButton = new QPushButton("Confirm changes");

    addWidget(label);
    addWidget(distance);
    addWidget(confirmButton);
    addStretch(1);

    connect(confirmButton, &QPushButton::clicked, this, &EdgeProp::getData);
}

void EdgeProp::setActiveEdge(Edge *edge) {
    activeEdge = edge;
    if(activeEdge){
        distance->setValue(activeEdge->getDistance());
    } else {
        distance->setValue(0);
    }
}

void EdgeProp::getData() {
    if(activeEdge){
        activeEdge->setDistance(distance->value());
        emit graphEdited();
    } else {
        distance->setValue(0);
    }
}

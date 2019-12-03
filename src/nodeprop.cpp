#include "nodeprop.h"

NodeProp::NodeProp(Graph* graph): graph(graph) {
    cityNameLab = new QLabel("City name");
    longitudeLab = new QLabel("Longitude [+ = E, - = W]");
    latitudeLab = new QLabel("Latitude [+ = N, - = S]");
    cityName = new QLineEdit();
    longitude = new QDoubleSpinBox();
    longitude->setRange(-180, 180);
    latitude = new QDoubleSpinBox();
    latitude->setRange(-90, 90);
    confirmButton = new QPushButton("Confirm changes");

    addWidget(cityNameLab);
    addWidget(cityName);
    addWidget(latitudeLab);
    addWidget(latitude);
    addWidget(longitudeLab);
    addWidget(longitude);
    addWidget(confirmButton);
    addStretch(1);

    connect(confirmButton, &QPushButton::clicked, this, &NodeProp::getData);
}

void NodeProp::setActiveNode(Node *node){
    activeNode = node;
    if(activeNode){
        cityName->setText(node->getName());
        longitude->setValue(node->pos().x());
        latitude->setValue(-node->pos().y());
    } else {
        cityName->setText("");
        longitude->setValue(0);
        latitude->setValue(0);
    }
}

void NodeProp::getData(){
    if(activeNode){
        QString city = cityName->text();
        if(city == activeNode->getName()){ //if name unchanged
            activeNode->setY(-latitude->value());
            activeNode->setX(longitude->value());
            emit graphEdited();
        } else if(!graph->isCityInGraph(city)){ //ensure valid city name
            activeNode->setName(city);
            activeNode->setY(-latitude->value());
            activeNode->setX(longitude->value());
            emit graphEdited();
        } //if both fails no update
    } else {
        cityName->setText("");
        longitude->setValue(0);
        latitude->setValue(0);
    }
}

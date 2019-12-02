#include "nodeproperties.h"
#include "ui_nodeproperties.h"

nodeProperties::nodeProperties(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nodeProperties)
{
    ui->setupUi(this);
}

nodeProperties::~nodeProperties()
{
    delete ui;
}

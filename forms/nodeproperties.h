#ifndef NODEPROPERTIES_H
#define NODEPROPERTIES_H

#include <QWidget>

namespace Ui {
class nodeProperties;
}

class nodeProperties : public QWidget
{
    Q_OBJECT

public:
    explicit nodeProperties(QWidget *parent = nullptr);
    ~nodeProperties();

private:
    Ui::nodeProperties *ui;
};

#endif // NODEPROPERTIES_H

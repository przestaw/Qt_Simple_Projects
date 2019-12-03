#ifndef NODEPROP_H
#define NODEPROP_H
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QPushButton>
#include "node.h"
#include "graph.h"

class NodeProp : public QVBoxLayout {
    Q_OBJECT
public:
    NodeProp(Graph* graph);
public slots:
    void setActiveNode(Node *node);
private slots:
    void getData();
signals:
    void graphEdited();
private:
    Graph *graph;
    Node *activeNode;
    QLabel *cityNameLab, *longitudeLab, *latitudeLab;
    QLineEdit *cityName;
    QDoubleSpinBox *longitude, *latitude;
    QPushButton *confirmButton;
};

#endif // NODEPROP_H

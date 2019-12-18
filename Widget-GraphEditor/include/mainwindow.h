#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include "graph.h"
#include "graphview.h"
#include "nodeprop.h"
#include "edgeprop.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class GraphEditorWindow : public QMainWindow{
    Q_OBJECT
public:
    GraphEditorWindow(QWidget *parent = nullptr);
    ~GraphEditorWindow();

    GraphView* getGraphicsView();
public slots:
    void renameNode(Node* node);
    void changeDistance(Edge* edge);
    void createNode(QPointF position);
    void createNode();

    void saveGraphToFile();
    void loadGraphFromFile();
    void newGraph();

    void updateMenu();
signals:
    void setActiveEdge(Edge* edge);
    void setActiveNode(Node* node);
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    Graph* graph();

    EdgeProp* edgeProp;
    NodeProp* nodeProp;
};
#endif // MAINWINDOW_H

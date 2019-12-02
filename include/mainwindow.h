#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <fstream>
#include "graph.h"
#include "graphview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    GraphView* getProgramView();
public slots:
    void renameNode(Node* node);
    void changeDistance(Edge* edge);
    void createNode(QPointF position);
    void createNode();

    void saveGraphToFile();
    void loadGraphFromFile();
    void newGraph();
signals:
    void addNode(Node* node);
    void cleanGraph();
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Graph graph;
};
#endif // MAINWINDOW_H

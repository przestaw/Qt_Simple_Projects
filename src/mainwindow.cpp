#include "mainwindow.h"
#include "../forms/ui_mainwindow.h"
#include "coordinatesgrid.h"
#include "graphview.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    connect(ui->actionAdd, SIGNAL(triggered()), this, SLOT(createNode()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newGraph()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveGraphToFile()));
    connect(ui->actionLoad_from_file, SIGNAL(triggered()), this, SLOT(loadGraphFromFile()));


    connect(ui->graphicsView, SIGNAL(removeNode(Node*)), &graph, SLOT(removeNode(Node*)));
    connect(ui->graphicsView, SIGNAL(removeEdge(Edge*)), &graph, SLOT(removeEdge(Edge*)));

    connect(&graph, &Graph::createdEdge, ui->graphicsView, &GraphView::addEdgeToScene);
    connect(ui->graphicsView, &GraphView::addEdge, &graph, &Graph::addEdge);
    connect(&graph, &Graph::createdNode, ui->graphicsView, &GraphView::addNodeToScene);

    connect(ui->graphicsView, SIGNAL(renameNode(Node*)), this, SLOT(renameNode(Node*)));
    connect(ui->graphicsView, SIGNAL(changeDist(Edge*)), this, SLOT(changeDistance(Edge*)));
    connect(ui->graphicsView, SIGNAL(createNode(QPointF)), this, SLOT(createNode(QPointF)));

    connect(this, SIGNAL(addNode(Node*)), &graph, SLOT(addNode(Node*)));

    Node *war = new Node(QPointF(-180, -90),"Warszawa");
    Node *wro = new Node(QPointF(180, 90), "Wroclaw");
    //Edge *edge= new Edge(war, wro);

    graph.addNode(war);
    graph.addNode(wro);
    graph.addEdgeByNodes(war, wro);

    ui->graphicsView->scene()->addItem(new CoordinatesGrid());

    ui->graphicsView->scene()->addItem(war);
    ui->graphicsView->scene()->addItem(wro);
}

MainWindow::~MainWindow(){
    delete ui;
}

GraphView *MainWindow::getProgramView(){
    return ui->graphicsView;
}

void MainWindow::renameNode(Node* node){
    bool entered = false;
    QString cityName = QInputDialog::getText(this, "Edit City Name", "City Name", QLineEdit::Normal, node->getName(), &entered);
    if(entered){
        node->setName(cityName);
    }
}

void MainWindow::changeDistance(Edge* edge){
    bool entered = false;
    double dist = QInputDialog::getDouble(this, "Edit Distance", "Distance", edge->getDistance(), 0., 2147483647., 6,  &entered);
    if(entered){
        edge->setDistance(dist);
    }
}

void MainWindow::createNode(QPointF position){
    bool entered = true; // double function -> determines to end procedure if user resigned or node is added
    QString cityName = QInputDialog::getText(this, "Edit City Name", "City Name", QLineEdit::Normal, "", &entered);
    if(true){ //TODO : validate name
        entered = false;
        emit addNode(new Node(position, cityName));
    } else {
        QMessageBox::warning(this, "ERROR", "City with that name exists");
        cityName = QInputDialog::getText(this, "Edit City Name", "City Name", QLineEdit::Normal, "", &entered);
    }
}

void MainWindow::createNode(){
    this->createNode(QPointF(0,0));
}

void MainWindow::saveGraphToFile(){
    QString newfilename;
    for (int i = 1; ; i++) {
        std::ifstream is(QDir::currentPath().toStdString() + "/graph" + std::to_string(i) + ".gph");
        if (!is.good()) {
            newfilename = QString::fromStdString(QDir::currentPath().toStdString() + "/graph" + std::to_string(i) + ".gph");
            break;
        }
    }
    QString userFilename = QFileDialog::getSaveFileName(this, "New Graph", newfilename, "Graph files (*.gph)",nullptr);
}

void MainWindow::loadGraphFromFile(){
    QString userFilename = QFileDialog::getOpenFileName(this, "Open Document", QDir::currentPath(), "Graph files (*.gph)", nullptr);
}

void MainWindow::newGraph(){
    //eventual save before
    emit cleanGraph();
}

void MainWindow::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Save Graph?",
                          "Your changes will be lost if you don't save them!",
                          QMessageBox::No|QMessageBox::Yes|QMessageBox::Cancel);
    if (reply == QMessageBox::Yes){
        saveGraphToFile();
    }else if (reply == QMessageBox::Cancel){
        event->ignore();
    }
}

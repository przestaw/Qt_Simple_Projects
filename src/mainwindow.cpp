#include "mainwindow.h"
#include "../forms/ui_mainwindow.h"
#include "coordinatesgrid.h"
#include "graphview.h"
#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    nodeProp = new NodeProp(&graph); //needed for data validation
    edgeProp = new EdgeProp();
    ui->stackedWidget->widget(1)->setLayout(nodeProp);
    ui->stackedWidget->widget(2)->setLayout(edgeProp);

    connect(this, SIGNAL(setActiveNode(Node*)), nodeProp, SLOT(setActiveNode(Node*)));
    connect(this, SIGNAL(setActiveEdge(Edge*)), edgeProp, SLOT(setActiveEdge(Edge*)));

    connect(this, SIGNAL(graphEdited()), ui->graphicsView, SLOT(invalidateScene()));
    connect(nodeProp, SIGNAL(graphEdited()), ui->graphicsView, SLOT(invalidateScene()));
    connect(edgeProp, SIGNAL(graphEdited()), ui->graphicsView, SLOT(invalidateScene()));

    connect(ui->actionAdd, SIGNAL(triggered()), this, SLOT(createNode()));
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newGraph()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveGraphToFile()));
    connect(ui->actionLoad_from_file, SIGNAL(triggered()), this, SLOT(loadGraphFromFile()));

    connect(ui->graphicsView->scene(), SIGNAL(selectionChanged()), this, SLOT(updateMenu()));

    connect(ui->graphicsView, SIGNAL(removeNode(Node*)), &graph, SLOT(removeNode(Node*)));
    connect(ui->graphicsView, SIGNAL(removeEdge(Edge*)), &graph, SLOT(removeEdge(Edge*)));

    connect(&graph, &Graph::createdEdge, ui->graphicsView, &GraphView::addEdgeToScene);
    connect(ui->graphicsView, &GraphView::addEdge, &graph, &Graph::addEdge);
    connect(&graph, &Graph::createdNode, ui->graphicsView, &GraphView::addNodeToScene);

    connect(ui->graphicsView, SIGNAL(renameNode(Node*)), this, SLOT(renameNode(Node*)));
    connect(ui->graphicsView, SIGNAL(changeDist(Edge*)), this, SLOT(changeDistance(Edge*)));
    connect(ui->graphicsView, SIGNAL(createNode(QPointF)), this, SLOT(createNode(QPointF)));

    connect(this, SIGNAL(addNode(Node*)), &graph, SLOT(addNode(Node*)));
    connect(this, SIGNAL(cleanGraph()), &graph, SLOT(eraseContents()));
    ui->graphicsView->scene()->addItem(new CoordinatesGrid());
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
        if(!graph.isCityInGraph(cityName)){
            node->setName(cityName);
            emit graphEdited();
        } // if cityName is in graph we can't update or it does not need update
    }
}

void MainWindow::changeDistance(Edge* edge){
    bool entered = false;
    double dist = QInputDialog::getDouble(this, "Edit Distance", "Distance", edge->getDistance(), 0., 2147483647., 6,  &entered);
    if(entered){
        edge->setDistance(dist);
        emit graphEdited();
    }
}

void MainWindow::createNode(QPointF position){
    bool entered = true; // double function -> determines to end procedure if user resigned or node is added
    QString cityName = QInputDialog::getText(this, "Edit City Name", "City Name", QLineEdit::Normal, "", &entered);
    if(entered){
        if(!graph.isCityInGraph(cityName)){
            entered = false;
            emit addNode(new Node(position, cityName));
        } else {
            QMessageBox::warning(this, "ERROR", "City with that name exists");
        }
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

    {//TODO : delete demo block
        Node *one = new Node(QPointF(21.07, -52.10),"Warszawa");
        Node *two = new Node(QPointF(-118, -34.5), "Los Angeles");
        Node *three = new Node(QPointF(139.24, -35.42), "Tokyo");
        Node *four = new Node(QPointF(25.44, 28.12), "Pretoria");
        Node *five = new Node(QPointF(149, 35.2), "Canberra");

        emit addNode(one);
        emit addNode(two);
        emit addNode(three);
        emit addNode(four);
        emit addNode(five);

        graph.addEdge(new Edge(one, two, 150));
        graph.addEdge(new Edge(one, three, 320));
        graph.addEdge(new Edge(one, four));
        graph.addEdge(new Edge(three, five));
    }
}

void MainWindow::newGraph(){
    //eventual save before
    emit cleanGraph();
    emit graphEdited();
}

void MainWindow::updateMenu() {
    auto selectedItems = ui->graphicsView->scene()->selectedItems();
    if (selectedItems.size() != 0) {
        auto item = selectedItems[0];
        if(item->type() == Node::Type){
            ui->stackedWidget->setCurrentIndex(1);
            emit setActiveNode(static_cast<Node*>(item));
        } else if(item->type() == Edge::Type){
            ui->stackedWidget->setCurrentIndex(2);
            emit setActiveEdge(static_cast<Edge*>(item));
        } else { //if sth elese got selected
            ui->stackedWidget->setCurrentIndex(0);
        }
    } else { //if nothing is selected
        ui->stackedWidget->setCurrentIndex(0);
    }
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

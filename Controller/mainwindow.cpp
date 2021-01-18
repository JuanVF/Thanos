#include <Controller/mainwindow.h>
#include "ui_mainwindow.h"

#include <Model/thanos.h>
#include <Model/Mundo/mundo.h>
#include <Model/filemanager.h>
#include <QMessageBox>
#include <QTreeWidgetItem>

// Estos son las que se encargan de hacer esas validaciones
// con las Regular Expression
// El string con simbolos raros es el RegEx
QRegularExpressionValidator * floatVal = new QRegularExpressionValidator(QRegularExpression("\\d+(\\.)?(\\d{1,5})?"), NULL);
QRegularExpressionValidator * intVal = new QRegularExpressionValidator(QRegularExpression("\\d+"), NULL);

int pages = 3;

Mundo * mundo = new Mundo();

void generateTreeView(Ui::MainWindow * ui);
void addTreeChild(Ui::MainWindow * ui, QTreeWidgetItem * item, TreeNode * tmp);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->leHumans->setValidator(intVal);

    // Inicializamos los humanos
    float time = clock();

    ui->taLog->appendPlainText("Generando los 10k humanos iniciales...");
    mundo->generateHumans(10000);
    mundo->generateTree();

    float since = (clock() - time)/1000.0;

    ui->taLog->appendPlainText(("Humanos generados en " + to_string(since) + " segundos...").c_str());

    ui->taLog->appendPlainText("Generando amigos...");

    time = clock();
    mundo->generateFriends();
    since = (clock() - time)/1000.0;

    ui->taLog->appendPlainText(("Amigos generados en " + to_string(since) + " segundos...").c_str());

    ui->taLog->appendPlainText("Generando familias...");

    time = clock();
    mundo->generateFamilies();
    since = (clock() - time)/1000.0;

    ui->taLog->appendPlainText(("Familias generadas en " + to_string(since) + " segundos...").c_str());

    generateTreeView(ui);
}

MainWindow::~MainWindow(){
    delete ui;
}

// Generamos las vistas del arbol
void generateTreeView(Ui::MainWindow * ui){
    ui->WorldTree->setColumnCount(2);

    QStringList labels;
    labels << "ID" << "Nombres";

    ui->WorldTree->setHeaderLabels(labels);

    QTreeWidgetItem * root = new QTreeWidgetItem(ui->WorldTree);

    Persona * raiz = mundo->arbol->raiz->persona->data;

    root->setText(0, to_string(raiz->ID).c_str());
    root->setText(1, (raiz->nombre + " " + raiz->apellido).c_str());

    ui->WorldTree->addTopLevelItem(root);

    addTreeChild(ui, root, mundo->arbol->raiz->hijoIzq);
    addTreeChild(ui, root, mundo->arbol->raiz->hijoDer);
}

// Generamos los hijos del arbol
void addTreeChild(Ui::MainWindow * ui, QTreeWidgetItem * item, TreeNode * tmp){
    if (tmp == NULL) return;

    QTreeWidgetItem * child = new QTreeWidgetItem();

    Persona * raiz = tmp->persona->data;

    child->setText(0, to_string(raiz->ID).c_str());
    child->setText(1, (raiz->nombre + " " + raiz->apellido).c_str());

    item->addChild(child);

    addTreeChild(ui, child, tmp->hijoIzq);
    addTreeChild(ui, child, tmp->hijoDer);
}

// Retorna un string con el texto de un lineedit
string getText(QLineEdit * le){
    return le->text().toStdString();
}

// Botones de avanzar paginas
void MainWindow::on_btnNext_clicked(){
    int index = ui->swContainer->currentIndex();

    if (index == pages)
        index = 0;
    else
        index++;

    ui->swContainer->setCurrentIndex(index);
}

void MainWindow::on_btnBack_clicked(){
    int index = ui->swContainer->currentIndex();

    if (index == 0)
        index = pages;
    else
        index--;

    ui->swContainer->setCurrentIndex(index);
}

// Boton de generar humanos
void MainWindow::on_btnHuman_clicked(){
    int amount = Utils::toInt(getText(ui->leHumans));

    if (amount < 100){
        QMessageBox msgBox;

        msgBox.setText("La cantidad minima de humanos es 100 para el correcto funcionamiento...");
        msgBox.exec();

        return;
    }

    ui->taLog->appendPlainText("Generando humanos...");

    float time = clock();
    mundo->generateHumans(amount);
    mundo->generateTree();
    float since = (clock() - time)/1000.0;

    ui->taLog->appendPlainText(("Humanos generados en " + to_string(since) + " segundos...").c_str());

    ui->taLog->appendPlainText("Generando amigos...");

    time = clock();
    mundo->generateFriends();
    since = (clock() - time)/1000.0;

    ui->taLog->appendPlainText(("Amigos generados en " + to_string(since) + " segundos...").c_str());

    ui->taLog->appendPlainText("Generando familias...");

    time = clock();
    mundo->generateFamilies();
    since = (clock() - time)/1000.0;

    ui->taLog->appendPlainText(("Familias generadas en " + to_string(since) + " segundos...").c_str());

    generateTreeView(ui);
}

void MainWindow::on_btnIDQuery_clicked(){
    int ID = Utils::toInt(getText(ui->leIDQuery));
}

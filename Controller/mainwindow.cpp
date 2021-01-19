#include <Controller/mainwindow.h>
#include "ui_mainwindow.h"

#include <Model/thanos.h>
#include <Model/Mundo/mundo.h>
#include <Model/Enemies/Nebula.h>
#include <Model/Enemies/ebony.h>
#include <Model/Enemies/blackdwarf.h>
#include <Model/Enemies/hashthanos.h>
#include <Model/Enemies/midnight.h>
#include <Model/Enemies/corvusGlaive.h>
#include <Model/Avengers/antman.h>
#include <Model/Avengers/ironman.h>
#include <Model/Avengers/spiderman.h>
#include <Model/Avengers/thor.h>
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
hashthanos * thanos = new hashthanos(mundo);

void generateTreeView(Ui::MainWindow * ui);
void addTreeChild(Ui::MainWindow * ui, QTreeWidgetItem * item, TreeNode * tmp);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    ui->leHumans->setValidator(intVal);
    ui->leIDQuery->setValidator(intVal);
    ui->leFamilyQuery->setValidator(intVal);

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

    for (int i = 0; i < (int) mundo->deportes.size(); i++){
        ui->comboBox->insertItem(i, mundo->deportes[i].c_str());
    }

    ui->taLog->appendPlainText("Generando tabla de dispersion de Thanos...");
    thanos->generateHashtable();
    ui->taLog->appendPlainText("Tabla de dispersion creada, revisar logs para ver datos...");
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
void MainWindow::on_pushButton_2_clicked(){
    int index = ui->swContainer->currentIndex();

    if (index == pages)
        index = 0;
    else
        index++;

    ui->swContainer->setCurrentIndex(index);
}

void MainWindow::on_pushButton_clicked(){
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

    ui->taLog->appendPlainText("Generando tabla de dispersion de Thanos...");
    thanos->generateHashtable();
    ui->taLog->appendPlainText("Tabla de dispersion creada, revisar logs para ver datos...");
}

void MainWindow::on_btnIDQuery_clicked(){
    int ID = Utils::toInt(getText(ui->leIDQuery));

    Persona * persona = mundo->getById(ID);

    if (persona == NULL){
        ui->taLog->appendPlainText("La persona no existe...\n");
    }else{
        ui->taLog->appendPlainText((persona->getInfo()+"\n").c_str());
    }
}

void MainWindow::on_btnFamilyQuery_clicked(){
    int ID = Utils::toInt(getText(ui->leFamilyQuery));

    Persona * persona = mundo->getById(ID);

    if (persona == NULL){
        ui->taLog->appendPlainText("La persona no existe...\n");
        return;
    }
    ui->taLog->appendPlainText("CONYUGUE: \n");

    if (persona->familia->conyugue == NULL){
        ui->taLog->appendPlainText("No tiene conyugue...\n");
    }else{
        ui->taLog->appendPlainText((persona->familia->conyugue->getInfo()+"\n").c_str());
    }

    ui->taLog->appendPlainText("HIJOS: \n");
    for (int i = 0; i < persona->familia->hijos->length; i++){
        ui->taLog->appendPlainText((persona->familia->hijos->get(i)->getInfo()+"\n").c_str());
    }
}

void MainWindow::on_btnFriendsQuery_clicked(){
    int ID = Utils::toInt(getText(ui->leFriendsQuery));

    Persona * persona = mundo->getById(ID);

    if (persona == NULL){
        ui->taLog->appendPlainText("La persona no existe...\n");
        return;
    }

    ui->taLog->appendPlainText("AMIGOS: \n\n");

    for (int i = 0; i < persona->amigos->length; i++){
        ui->taLog->appendPlainText((persona->amigos->get(i)->getInfo()+"\n").c_str());
    }
}

void MainWindow::on_btnFamilyQuery_3_clicked(){
    int cantidad = mundo->getAlivePeople();

    ui->taLog->appendPlainText(("Cantidad de personas vivas: " + to_string(cantidad)).c_str());
}

void MainWindow::on_btnDeadQuery_clicked(){
    int cantidad = mundo->getDeathPeople();

    ui->taLog->appendPlainText(("Cantidad de personas muertas: " + to_string(cantidad)).c_str());
}

void MainWindow::on_btnData_clicked(){
    int names = Utils::toInt(getText(ui->leNames));
    int last = Utils::toInt(getText(ui->leLastNames));
    int prof = Utils::toInt(getText(ui->leJobs));

    if (names >= (int) mundo->nombresFem.size()){
        ui->taLog->appendPlainText(("La cantidad de nombres es mayor a la cantidad permitida, ajustando a: " + to_string(mundo->nombresFem.size()) + "\n").c_str());
    }

    if (last >= (int) mundo->apellidos.size()){
        ui->taLog->appendPlainText(("La cantidad de apellidos es mayor a la cantidad permitida, ajustando a: " + to_string(mundo->apellidos.size()) + "\n").c_str());
    }

    if (prof >= (int) mundo->profesiones.size()){
        ui->taLog->appendPlainText(("La cantidad de profesiones es mayor a la cantidad permitida, ajustando a: " + to_string(mundo->profesiones.size()) + "\n").c_str());
    }

    mundo->reLoad(names, last, mundo->creencias.size() - 1, prof, mundo->paises.size() - 1, mundo->deportes.size()-1);

    ui->taLog->appendPlainText("Cambios generados!");
}

void MainWindow::on_btnNebula_clicked(){
    Nebula * nebula = new Nebula(mundo);

    ui->taLog->appendPlainText("Ejecutando algoritmo de Nebula...");
    nebula->kill();
    ui->taLog->appendPlainText("Algoritmo ejecutado... Ver logs generados para comprobar datos...");
}

void MainWindow::on_btnEbony_clicked(){
    int ID = Utils::toInt(getText(ui->leEbony));

    Ebony * ebony = new Ebony(mundo);

    Persona * tmp = mundo->getById(ID);

    if (tmp == NULL){
        ui->taLog->appendPlainText("Esa ID no existe...\n");

        return;
    }

    ui->taLog->appendPlainText("Ejecutando algoritmo de Ebony\n");
    ebony->kill(ID);
    ui->taLog->appendPlainText("Algoritmo ejecutado... Ver logs generados para comprobar datos...\n");
}

void MainWindow::on_btnBlackD_clicked(){
    string selected = ui->comboBox->currentText().toStdString();

    BlackDwarf * bd = new BlackDwarf(mundo);

    ui->taLog->appendPlainText("Ejecutando algoritmo de Ebony\n");
    bd->kill(selected);
    ui->taLog->appendPlainText("Algoritmo ejecutado... Ver logs generados para comprobar datos...\n");
}

void MainWindow::on_btnThanos_clicked(){
    int level = Utils::toInt(getText(ui->leThanosLevel));

    thanos->killByLevel(level);
    ui->taLog->appendPlainText("Humano asesinado, revisar logs para ver datos...\n");
}

void MainWindow::on_btnThanosYear_clicked(){
    int year = Utils::toInt(getText(ui->leThanosYear));

    thanos->killByYear(year);
    ui->taLog->appendPlainText("Humano asesinado, revisar logs para ver datos...\n");
}

void MainWindow::on_btnThanosB_clicked(){
    int year = Utils::toInt(getText(ui->leThanosYear));
    int level = Utils::toInt(getText(ui->leThanosLevel));

    thanos->killByLevelAndYear(year, level);
    ui->taLog->appendPlainText("Humano asesinado, revisar logs para ver datos..\n.");
}

void MainWindow::on_btnMidnight_clicked(){
    Midnight * mid = new Midnight(mundo);

    ui->taLog->appendPlainText("Ejecutando algoritmo de Midnight\n");
    mid->kill();
    ui->taLog->appendPlainText("Humanos asesinados, revisar logs para ver datos...\n");
}

void MainWindow::on_btnCorvus_clicked(){
    CorvusGlaive * cv = new CorvusGlaive(mundo);

    ui->taLog->appendPlainText("Ejecutando algoritmo de Corvus Glaive\n");
    cv->kill();
    ui->taLog->appendPlainText("Humanos asesinados, revisar logs para ver datos...\n");
}

void MainWindow::on_btnAntMan_clicked(){
    int ants = Utils::toInt(getText(ui->leAntMan));

    Antman * ant = new Antman(mundo);

    ant->save(ants);
    ui->taLog->appendPlainText("Humanos salvados, revisar logs para ver datos...\n");
}

void MainWindow::on_btnIronMan_clicked(){
    IronMan * iron = new IronMan(mundo);

    iron->save();
    ui->taLog->appendPlainText("Humanos salvados, revisar logs para ver datos...\n");
}

void MainWindow::on_btnThor_clicked(){
    Thor * thor = new Thor(mundo);
    int nivel = Utils::toInt(getText(ui->leThor));

    thor->save(nivel);
    ui->taLog->appendPlainText("Humanos salvados, revisar logs para ver datos...\n");
}

void MainWindow::on_btnSpiderMan_clicked(){
    SpiderMan * spider = new SpiderMan(mundo);

    spider->save();
    ui->taLog->appendPlainText("Humanos salvados, revisar logs para ver datos...\n");
}
